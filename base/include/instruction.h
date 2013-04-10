#ifndef LLVM_HS_INSTRUCTION_H
#define LLVM_HS_INSTRUCTION_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned LLVMReturnInstGetNumSuccessors(LLVMValueRef ReturnInstr);

LLVMValueRef LLVMReturnInstGetReturnValue(LLVMValueRef ReturnInstr);

LLVMBool LLVMBrInstIsConditional(LLVMValueRef Br);

unsigned LLVMAllocaGetAlignment(LLVMValueRef Alloca);

LLVMTypeRef LLVMAllocaGetAllocatedType(LLVMValueRef Alloca);

unsigned LLVMStoreGetAlignment(LLVMValueRef Store);

unsigned LLVMLoadGetAlignment(LLVMValueRef Load);

LLVMBool LLVMReturnInstHasReturnValue(LLVMValueRef Return);

LLVMTypeRef LLVMGetFunctionType(LLVMValueRef Fn);

LLVMTypeRef LLVMGetFunctionReturnType(LLVMValueRef Fn);

LLVMBool LLVMHasUnnamedAddr(LLVMValueRef Global);

LLVMValueRef LLVMSelectGetCondition(LLVMValueRef Select);

LLVMValueRef LLVMSelectGetTrueValue(LLVMValueRef Select);

LLVMValueRef LLVMSelectGetFalseValue(LLVMValueRef Select);

unsigned LLVMExtractValueGetNumIndices(LLVMValueRef ExtractVal);

void LLVMExtractValueGetIndices(LLVMValueRef ExtractVal, unsigned *Indices);

unsigned LLVMInsertValueGetNumIndices(LLVMValueRef InsertVal);

void LLVMInsertValueGetIndices(LLVMValueRef InsertVal, unsigned *Indices);

unsigned LLVMAtomicRMWGetOperation(LLVMValueRef AtomicRMW);

unsigned LLVMAtomicRMWGetOrdering(LLVMValueRef AtomicRMW);

unsigned LLVMAtomicCmpXchgGetOrdering(LLVMValueRef AtomicCmpXchg);

LLVMValueRef LLVMGetAggregateOperand(LLVMValueRef Insert);

LLVMValueRef LLVMGetInsertedValueOperand(LLVMValueRef Insert);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LLVM_HS_INSTRUCTION_H */
