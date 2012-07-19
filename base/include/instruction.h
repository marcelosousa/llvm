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

LLVMBool LLVMReturnInstHasReturnValue(LLVMValueRef Return);

LLVMTypeRef LLVMGetFunctionReturnType(LLVMValueRef Fn);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LLVM_HS_INSTRUCTION_H */
