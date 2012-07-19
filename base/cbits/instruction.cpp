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

