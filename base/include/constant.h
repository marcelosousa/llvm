#ifndef LLVM_HS_CONSTANT_H
#define LLVM_HS_CONSTANT_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
  LLVMBlockAddr,
  LLVMConstantAggregateZero,
  LLVMConstantArray,
  LLVMConstantDataSequential,
  LLVMConstantExpr,
  LLVMConstantFP,
  LLVMConstantInt,
  LLVMConstantPointerNull,
  LLVMConstantStruct,
  LLVMConstantVector,
  LLVMGlobalValue,
  LLVMUndefValue
} LLVMConstantClass;

typedef enum {
  LLVMFunction,
  LLVMGlobalAlias,
  LLVMGlobalVariable
} LLVMGlobalValueClass;

typedef enum {
  LLVMConstantDataArray,
  LLVMConstantDataVector
} LLVMConstantDataSequentialClass;

LLVMConstantClass LLVMGetConstantClass(LLVMValueRef Val);

LLVMGlobalValueClass LLVMGetGlobalValueClass(LLVMValueRef GlobalVal);

LLVMConstantDataSequentialClass LLVMGetConstantDataSequentialClass(LLVMValueRef CDataSequential);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LLVM_HS_CONSTANT_H */
