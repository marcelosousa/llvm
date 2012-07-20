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

LLVMBool LLVMReturnInstHasReturnValue(LLVMValueRef Return);

LLVMTypeRef LLVMGetFunctionReturnType(LLVMValueRef Fn);

const char *LLVMGetConstantTy(LLVMValueRef Val);

LLVMBool LLVMConstantValueIsString(LLVMValueRef Val);

LLVMTypeRef LLVMConstantValueGetElemType(LLVMValueRef Val);

unsigned LLVMConstantValueGetNumElem(LLVMValueRef Val);

const char *LLVMConstantValueGetAsString(LLVMValueRef Val);

unsigned LLVMConstantValueGetElemByteSize(LLVMValueRef Val);

LLVMBool LLVMHasUnnamedAddr(LLVMValueRef Global);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LLVM_HS_INSTRUCTION_H */
