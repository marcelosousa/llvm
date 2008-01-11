{-# LANGUAGE ScopedTypeVariables, MultiParamTypeClasses, FunctionalDependencies, FlexibleInstances, TypeSynonymInstances, UndecidableInstances, FlexibleContexts #-}
module LLVM.Core.CodeGen(
    -- * Module creation
    newModule, newNamedModule, defineModule, createModule,
    -- * Globals
    Linkage(..),
    -- * Function creation
    Function, newFunction, newNamedFunction, defineFunction, createFunction,
    FunctionArgs,
    -- * Global variable creation
    Global, newGlobal, newNamedGlobal, defineGlobal, createGlobal, TGlobal,
    externFunction, TFunction,
    -- * Values
    Value(..), ConstValue(..),
    IsConst(..), valueOf, value,
    constString, constStringNul,
    -- * Basic blocks
    BasicBlock(..), newBasicBlock, newNamedBasicBlock, defineBasicBlock, createBasicBlock,
    -- * Misc
    withCurrentBuilder
    ) where
import Control.Monad(liftM)
import Data.Int
import Data.Word
import Data.TypeNumbers
import LLVM.Core.CodeGenMonad
import qualified LLVM.Core.FFI as FFI
import qualified LLVM.Core.Util as U
import LLVM.Core.Type
import LLVM.Core.Data

--------------------------------------

newModule :: IO U.Module
newModule = newNamedModule "_module"  -- XXX should generate a name

newNamedModule :: String -> IO U.Module
newNamedModule = U.createModule

defineModule :: U.Module -> CodeGenModule a -> IO a
defineModule = runCodeGenModule

createModule :: CodeGenModule a -> IO a
createModule cgm = newModule >>= \ m -> defineModule m cgm

--------------------------------------

newtype Value a = Value FFI.ValueRef

newtype ConstValue a = ConstValue FFI.ValueRef

class (IsType a) => IsConst a where
    constOf :: a -> ConstValue a

instance IsConst Bool   where
  constOf i = ConstValue $ FFI.constInt (typeRef i) (fromIntegral $ fromEnum i) 0
instance IsConst Word8  where constOf = constI False
instance IsConst Word16 where constOf = constI False
instance IsConst Word32 where constOf = constI False
instance IsConst Word64 where constOf = constI False
instance IsConst Int8   where constOf = constI True
instance IsConst Int16  where constOf = constI True
instance IsConst Int32  where constOf = constI True
instance IsConst Int64  where constOf = constI True
instance IsConst Float  where constOf = constF
instance IsConst Double where constOf = constF
--instance IsConst FP128  where constOf = constF

constI :: (IsType a, Integral a) => Bool -> a -> ConstValue a
constI signed i = ConstValue $ FFI.constInt (typeRef i) (fromIntegral i)
       	      	  	       		    (fromIntegral $ fromEnum signed)

constF :: (IsType a, Real a) => a -> ConstValue a
constF i = ConstValue $ FFI.constReal (typeRef i) (realToFrac i)

valueOf :: (IsConst a) => a -> Value a
valueOf = value . constOf

value :: ConstValue a -> Value a
value (ConstValue a) = Value a

constString :: String -> ConstValue (Array AnySize Word8)
constString = ConstValue . U.constString

constStringNul :: String -> ConstValue (Array AnySize Word8)
constStringNul = ConstValue . U.constStringNul

--------------------------------------

type FunctionRef = FFI.ValueRef

-- |A function is simply a pointer to the function.
type Function a = Value (Ptr a)

createFunction :: (IsFunction f, FunctionArgs f g (CodeGenFunction r ())) =>
                  g -> CodeGenModule (Function f)
createFunction body = do
    f <- newFunction
    defineFunction f body
    return f

newFunction :: forall a . (IsFunction a) => CodeGenModule (Function a)
newFunction = genMSym >>= newNamedFunction

newNamedFunction :: forall a . (IsFunction a) => String -> CodeGenModule (Function a)
newNamedFunction name = do
     m <- getModule
     let typ = typeRef (undefined :: a)
     liftIO $ liftM Value $ U.addFunction m name typ

defineFunction :: forall f g r . (FunctionArgs f g (CodeGenFunction r ())) =>
                  Function f -> g -> CodeGenModule ()
defineFunction (Value fn) body = do
    bld <- liftIO $ U.createBuilder
    let body' = do
	    l <- newBasicBlock
	    defineBasicBlock l
	    applyArgs fn body :: CodeGenFunction r ()
    runCodeGenFunction bld fn body'
    return ()

-- XXX This is ugly, it must be possible to make it simpler
-- Convert a function of type f = t1->t2->...->r to
-- g = Value t1 -> Value t2 -> ... CodeGenFunction r ()
class FunctionArgs f g r | f -> g r, g r -> f where
    apArgs :: Int -> FunctionRef -> g -> r

applyArgs :: (FunctionArgs f g r) => FunctionRef -> g -> r
applyArgs f g = apArgs 0 f g

instance (FunctionArgs b b' r) => FunctionArgs (a -> b) (Value a -> b') r where
    apArgs n f g = apArgs (n+1) f (g $ Value $ U.getParam f n)

-- XXX instances for all IsFirstClass functions,
-- because Haskell can't deal with the context and the FD
type FA a = CodeGenFunction a ()
instance FunctionArgs Float        (FA Float)        (FA Float)        where apArgs _ _ g = g
instance FunctionArgs Double       (FA Double)       (FA Double)       where apArgs _ _ g = g
instance FunctionArgs FP128        (FA FP128)        (FA FP128)        where apArgs _ _ g = g
instance (IsTypeNumber n) => 
         FunctionArgs (IntN n)     (FA (IntN n))     (FA (IntN n))     where apArgs _ _ g = g
instance (IsTypeNumber n) =>
         FunctionArgs (WordN n)    (FA (WordN n))    (FA (WordN n))    where apArgs _ _ g = g
instance FunctionArgs Bool         (FA Bool)         (FA Bool)         where apArgs _ _ g = g
instance FunctionArgs Int8         (FA Int8)         (FA Int8)         where apArgs _ _ g = g
instance FunctionArgs Int16        (FA Int16)        (FA Int16)        where apArgs _ _ g = g
instance FunctionArgs Int32        (FA Int32)        (FA Int32)        where apArgs _ _ g = g
instance FunctionArgs Int64        (FA Int64)        (FA Int64)        where apArgs _ _ g = g
instance FunctionArgs Word8        (FA Word8)        (FA Word8)        where apArgs _ _ g = g
instance FunctionArgs Word16       (FA Word16)       (FA Word16)       where apArgs _ _ g = g
instance FunctionArgs Word32       (FA Word32)       (FA Word32)       where apArgs _ _ g = g
instance FunctionArgs Word64       (FA Word64)       (FA Word64)       where apArgs _ _ g = g
instance (IsTypeNumber n, IsPrimitive a) =>
         FunctionArgs (Vector n a) (FA (Vector n a)) (FA (Vector n a)) where apArgs _ _ g = g
instance (IsType a) => 
         FunctionArgs (Ptr a)      (FA (Ptr a))      (FA (Ptr a))      where apArgs _ _ g = g

--------------------------------------

newtype BasicBlock = BasicBlock FFI.BasicBlockRef

createBasicBlock :: CodeGenFunction r BasicBlock
createBasicBlock = do
    b <- newBasicBlock
    defineBasicBlock b
    return b

newBasicBlock :: CodeGenFunction r BasicBlock
newBasicBlock = genFSym >>= newNamedBasicBlock

newNamedBasicBlock :: String -> CodeGenFunction r BasicBlock
newNamedBasicBlock name = do
    fn <- getFunction
    liftIO $ liftM BasicBlock $ U.appendBasicBlock fn name

defineBasicBlock :: BasicBlock -> CodeGenFunction r ()
defineBasicBlock (BasicBlock l) = do
    bld <- getBuilder
    liftIO $ U.positionAtEnd bld l

--------------------------------------

withCurrentBuilder :: (FFI.BuilderRef -> IO a) -> CodeGenFunction r a
withCurrentBuilder body = do
    bld <- getBuilder
    liftIO $ U.withBuilder bld body

--------------------------------------

-- Mark all block terminating instructions.  Not used yet.
--data Terminate = Terminate

--------------------------------------

type AnySize = End
type Global a = Value (Ptr a)

-- XXX what's the right type?
newNamedGlobal :: forall a . (IsType a) => Linkage -> String -> TGlobal a
newNamedGlobal linkage name = do
    modul <- getModule
    let typ = typeRef (undefined :: a)
    liftIO $ liftM Value $ U.addGlobal modul (fromIntegral $ fromEnum linkage) name typ

newGlobal :: forall a . (IsType a) => Linkage -> TGlobal a
newGlobal linkage = genMSym "glb" >>= newNamedGlobal linkage

defineGlobal :: Global a -> ConstValue a -> CodeGenModule ()
defineGlobal (Value g) (ConstValue v) =
    liftIO $ FFI.setInitializer g v

createGlobal :: (IsType a) => Linkage -> ConstValue a -> TGlobal a
createGlobal linkage con = do
    g <- newGlobal linkage
    defineGlobal g con
    return g

type TFunction a = CodeGenModule (Function a)
type TGlobal a = CodeGenModule (Global a)

externFunction :: forall f . (IsFunction f) => String -> TFunction f
externFunction name = do
    m <- getModule
    liftM Value $ liftIO $ U.getExternFunction m name (typeRef (undefined :: f))

--------------------------------------

-- |An enumeration for the kinds of linkage for global values.
data Linkage
    = ExternalLinkage     -- ^Externally visible function
    | LinkOnceLinkage     -- ^Keep one copy of function when linking (inline)
    | WeakLinkage         -- ^Keep one copy of named function when linking (weak)
    | AppendingLinkage    -- ^Special purpose, only applies to global arrays
    | InternalLinkage     -- ^Rename collisions when linking (static functions)
    | DLLImportLinkage    -- ^Function to be imported from DLL
    | DLLExportLinkage    -- ^Function to be accessible from DLL
    | ExternalWeakLinkage -- ^ExternalWeak linkage description
    | GhostLinkage        -- ^Stand-in functions for streaming fns from BC files    
    deriving (Show, Eq, Ord, Enum)

{-
-- |An enumeration for the kinds of visibility of global values.
data VisibilityTypes
    = DefaultVisibility   -- ^The GV is visible
    | HiddenVisibility    -- ^The GV is hidden
    | ProtectedVisibility -- ^The GV is protected
    deriving (Show, Eq, Ord, Enum)
-}
