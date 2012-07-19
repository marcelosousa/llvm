#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "hs_llvm_config.h"

#include "llvm-c/Core.h"

#include "instruction.h"

using namespace llvm;

/*--.. Operations on return instructions ..................................--*/
unsigned LLVMReturnInstGetNumSuccessors(LLVMValueRef Return){
  return unwrap<ReturnInst>(Return)->getNumSuccessors();
}

LLVMBool LLVMReturnInstHasReturnValue(LLVMValueRef Return){
  Value *Val = unwrap<ReturnInst>(Return)->getReturnValue();
  if(Val)
    return 1;
  else
    return 0;
}

LLVMValueRef LLVMReturnInstGetReturnValue(LLVMValueRef Return){
  return wrap(unwrap<ReturnInst>(Return)->getReturnValue());
}


/*--.. Operations on branch instruction ....................................--*/
LLVMBool LLVMBrInstIsConditional(LLVMValueRef Br){
  return unwrap<BranchInst>(Br)->isConditional();
}

/*--.. Operations on alloca instruction ....................................--*/
unsigned LLVMAllocaGetAlignment(LLVMValueRef Alloca) {
  return unwrap<AllocaInst>(Alloca)->getAlignment();
}

LLVMTypeRef LLVMAllocaGetAllocatedType(LLVMValueRef Alloca){
  return wrap(unwrap<AllocaInst>(Alloca)->getAllocatedType());
}

LLVMTypeRef LLVMGetFunctionReturnType(LLVMValueRef Fn){
  return wrap(unwrap<Function>(Fn)->getReturnType());
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

unsigned LLVMConstantValueGetElemByteSize(LLVMValueRef Val){
  if (Constant *C = dyn_cast<Constant>(unwrap(Val))){
   if(isa<ConstantDataSequential>(C)){
    ConstantDataSequential *CD = dyn_cast<ConstantDataSequential>(C);
    return CD->getElementByteSize();
   }
  }
}

LLVMBool LLVMHasUnnamedAddr(LLVMValueRef Global){
   return unwrap<GlobalValue>(Global)->hasUnnamedAddr();
}
