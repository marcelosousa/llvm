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

const char *LLVMGetConstantTy(LLVMValueRef Val);

LLVMBool LLVMConstantValueIsString(LLVMValueRef Val);

LLVMTypeRef LLVMConstantValueGetElemType(LLVMValueRef Val);

unsigned LLVMConstantValueGetNumElem(LLVMValueRef Val);

const char *LLVMConstantValueGetAsString(LLVMValueRef Val);

unsigned LLVMConstantValueGetElemByteSize(LLVMValueRef Val);

LLVMTypeRef LLVMConstantArrayGetType(LLVMValueRef Val);

unsigned LLVMArrayTypeGetNumElements(LLVMTypeRef Ty);

LLVMTypeRef LLVMConstantStructGetType(LLVMValueRef Val);

unsigned LLVMStructTypeGetNumElements(LLVMTypeRef Ty);

LLVMBool LLVMHasNameStruct(LLVMTypeRef StructTy);

unsigned LLVMConstGetNumOperands(LLVMValueRef Val);

LLVMValueRef LLVMConstGetOperand(LLVMValueRef Val, unsigned Index);

//float LLVMGetFPValue(LLVMValueRef C);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LLVM_HS_CONSTANT_H */
