#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "hs_llvm_config.h"

#include "llvm-c/Core.h"

#include "ConstantsContext.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/GlobalAlias.h"
#include "llvm/IR/Function.h"
#include "constant.h"

using namespace llvm;

LLVMConstantClass LLVMGetConstantClass(LLVMValueRef Val){
  Constant *C = dyn_cast<Constant>(unwrap(Val));
  assert(C);

  if(isa<BlockAddress>(C))
     return LLVMBlockAddr;
  else if(isa<ConstantAggregateZero>(C))
     return LLVMConstantAggregateZero;
  else if(isa<ConstantArray>(C))
     return LLVMConstantArray;
  else if(isa<ConstantDataSequential>(C))
     return LLVMConstantDataSequential;
  else if(isa<ConstantExpr>(C))
     return LLVMConstantExpr; 
  else if(isa<ConstantFP>(C))
     return LLVMConstantFP;
  else if(isa<ConstantInt>(C))
     return LLVMConstantInt;
  else if(isa<ConstantPointerNull>(C))
     return LLVMConstantPointerNull;
  else if(isa<ConstantStruct>(C))
     return LLVMConstantStruct;
  else if(isa<ConstantVector>(C))
     return LLVMConstantVector;
  else if(isa<GlobalValue>(C))
     return LLVMGlobalValue;
  else
     return LLVMUndefValue;
}

LLVMGlobalValueClass LLVMGetGlobalValueClass(LLVMValueRef GlobalVal){
  GlobalValue *GV = dyn_cast<GlobalValue>(unwrap(GlobalVal));
  assert(GV);

  if(isa<Function>(GV))
     return LLVMFunction;
  else if(isa<GlobalAlias>(GV))
     return LLVMGlobalAlias;
  else
     return LLVMGlobalVariable;
}

/******** Constant Data Sequential  */
LLVMConstantDataSequentialClass LLVMGetConstantDataSequentialClass(LLVMValueRef CDataSequential){
  ConstantDataSequential *CDS = dyn_cast<ConstantDataSequential>(unwrap(CDataSequential));
  assert(CDS);

  if(isa<ConstantDataArray>(CDS))
     return LLVMConstantDataArray;
  else 
     return LLVMConstantDataVector;
}

const char *LLVMGetConstantTy(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<BlockAddress>(C))
      return "block address";
   else if(isa<ConstantArray>(C))
      return "constant array";
   else if(isa<ConstantDataSequential>(C))
      return "constant data sequential";
   else if(isa<GlobalValue>(C))
      return "global value";
   else if(isa<ConstantStruct>(C))
      return "global struct";
   else if(isa<ConstantVector>(C))
      return "constant vector";
   else if(isa<ConstantInt>(C))
      return "constant int";
   else if(isa<UndefValue>(C))
      return "undef value";
   else
      return "incomplete";
  }
  return "bad";
}

LLVMBool LLVMConstantValueIsString(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<ConstantDataSequential>(C)){
    ConstantDataSequential *CD = dyn_cast<ConstantDataSequential>(C);
    return CD->isString();
   }
  }

}

LLVMTypeRef LLVMConstantValueGetElemType(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<ConstantDataSequential>(C)){
    ConstantDataSequential *CD = dyn_cast<ConstantDataSequential>(C);
    return wrap(CD->getElementType());
   }
  }
}

unsigned LLVMConstantValueGetNumElem(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<ConstantDataSequential>(C)){
    ConstantDataSequential *CD = dyn_cast<ConstantDataSequential>(C);
    return CD->getNumElements();
   }
  }
}

const char *LLVMConstantValueGetAsString(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<ConstantDataSequential>(C)){
    ConstantDataSequential *CD = dyn_cast<ConstantDataSequential>(C);
    return CD->getAsString().data();
   }
  }
}

const char *LLVMConstantValueGetRawDataValues(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<ConstantDataSequential>(C)){
    ConstantDataSequential *CD = dyn_cast<ConstantDataSequential>(C);
    return CD->getRawDataValues().data();
   }
  }
}

unsigned LLVMConstantValueGetElemByteSize(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<ConstantDataSequential>(C)){
    ConstantDataSequential *CD = dyn_cast<ConstantDataSequential>(C);
    return CD->getElementByteSize();
   }
  }
}

LLVMTypeRef LLVMConstantArrayGetType(LLVMValueRef Val){
  Constant *C = dyn_cast<Constant>(unwrap(Val));
  assert(C);
  ConstantArray *CA = dyn_cast<ConstantArray>(C);
  assert(CA);
  return wrap(C->getType());
}

unsigned LLVMArrayTypeGetNumElements(LLVMTypeRef Ty){
  ArrayType *AT = dyn_cast<ArrayType>(unwrap(Ty));
  assert(AT);
  return AT->getNumElements();
}

LLVMTypeRef LLVMConstantStructGetType(LLVMValueRef Val){
  Constant *C = dyn_cast<Constant>(unwrap(Val));
  assert(C);
  ConstantStruct *CA = dyn_cast<ConstantStruct>(C);
  assert(CA);
  return wrap(C->getType());
}

LLVMBool LLVMHasNameStruct(LLVMTypeRef StructTy) {
  return unwrap<StructType>(StructTy)->hasName();
}

unsigned LLVMStructTypeGetNumElements(LLVMTypeRef Ty){
  StructType *ST = dyn_cast<StructType>(unwrap(Ty));
  assert(ST);
  return ST->getNumElements();
}

unsigned LLVMConstGetNumOperands(LLVMValueRef Val){
  Constant *C = dyn_cast<Constant>(unwrap(Val));
  assert(C);
  return C->getNumOperands();
}

LLVMValueRef LLVMConstGetOperand(LLVMValueRef Val, unsigned Index) {
  Constant *C = dyn_cast<Constant>(unwrap(Val));
  return wrap(C->getOperand(Index));
}

LLVMConstantFPClass LLVMGetConstantFPClass(LLVMValueRef C){
  ConstantFP *CFP = dyn_cast<ConstantFP>(unwrap(C));
  assert(CFP);

  if(CFP->getType()->isFloatTy())
     return LLVMFloatValue;
  else 
     return LLVMDoubleValue;
}

float LLVMGetFPValueFloat(LLVMValueRef C){
  ConstantFP *CFP = dyn_cast<ConstantFP>(unwrap(C));
  assert(CFP);

  return CFP->getValueAPF().convertToFloat();
}

double LLVMGetFPValueDouble(LLVMValueRef C){
  ConstantFP *CFP = dyn_cast<ConstantFP>(unwrap(C));
  assert(CFP);

  return CFP->getValueAPF().convertToDouble();
}

unsigned LLVMConstCompareGetPredicate(LLVMValueRef Val){
  ConstantExpr *CE = dyn_cast<ConstantExpr>(unwrap(Val));
  return ((const CompareConstantExpr*)CE)->predicate;
}

const char *LLVMInlineAsmString(LLVMValueRef Val){
  InlineAsm *IA = dyn_cast<InlineAsm>(unwrap(Val));
  return IA->getAsmString().c_str();
}

const char *LLVMInlineAsmConstrString(LLVMValueRef Val){
  InlineAsm *IA = dyn_cast<InlineAsm>(unwrap(Val));
  return IA->getConstraintString().c_str();
}

LLVMBool LLVMInlineAsmHasSideEffects(LLVMValueRef Val) {
  return unwrap<InlineAsm>(Val)->hasSideEffects();
}

LLVMBool LLVMInlineAsmIsAlignStack(LLVMValueRef Val) {
  return unwrap<InlineAsm>(Val)->isAlignStack();
}

unsigned LLVMInlineAsmGetDialect(LLVMValueRef Val) {
  return unwrap<InlineAsm>(Val)->getDialect();
}