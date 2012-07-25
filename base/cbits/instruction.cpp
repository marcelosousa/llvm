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

/*--.. Operations on store instruction ....................................--*/
unsigned LLVMStoreGetAlignment(LLVMValueRef Store){
  return unwrap<StoreInst>(Store)->getAlignment(); 
}

unsigned LLVMLoadGetAlignment(LLVMValueRef Load){
  return unwrap<LoadInst>(Load)->getAlignment(); 
}

LLVMTypeRef LLVMGetFunctionReturnType(LLVMValueRef Fn){
  return wrap(unwrap<Function>(Fn)->getReturnType());
}

LLVMBool LLVMHasUnnamedAddr(LLVMValueRef Global){
   return unwrap<GlobalValue>(Global)->hasUnnamedAddr();
}

/*--.. Operations on select instruction ..................................--*/
LLVMValueRef LLVMSelectGetCondition(LLVMValueRef Select){
  return wrap(unwrap<SelectInst>(Select)->getCondition());
}

LLVMValueRef LLVMSelectGetTrueValue(LLVMValueRef Select){
  return wrap(unwrap<SelectInst>(Select)->getTrueValue());
}

LLVMValueRef LLVMSelectGetFalseValue(LLVMValueRef Select){
  return wrap(unwrap<SelectInst>(Select)->getFalseValue());
}

unsigned LLVMExtractValueGetNumIndices(LLVMValueRef ExtractVal) {
  ExtractValueInst *extr = unwrap<ExtractValueInst>(ExtractVal);
  assert(extr);
  return extr->getNumIndices();
}

void LLVMExtractValueGetIndices(LLVMValueRef ExtractVal, unsigned *Indices) {
  ExtractValueInst *extr = unwrap<ExtractValueInst>(ExtractVal);
  assert(extr);
  for (ExtractValueInst::idx_iterator I = extr->idx_begin(), E = extr->idx_end(); I!=E; I++)
    *Indices++ = *I;
//  return extr->getIndices().data();
}

unsigned LLVMAtomicRMWGetOperation(LLVMValueRef AtomicRMW){
  AtomicRMWInst *atomic = unwrap<AtomicRMWInst>(AtomicRMW);
  assert(atomic);
  return atomic->getOperation();
}

unsigned LLVMAtomicRMWGetOrdering(LLVMValueRef AtomicRMW){
  AtomicRMWInst *atomic = unwrap<AtomicRMWInst>(AtomicRMW);
  assert(atomic);
  return atomic->getOrdering();
}
