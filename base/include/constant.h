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

typedef enum {
  LLVMFloatValue,
  LLVMDoubleValue
} LLVMConstantFPClass;

const char *LLVMInlineAsmString(LLVMValueRef Val);

const char *LLVMInlineAsmConstrString(LLVMValueRef Val);

LLVMBool LLVMInlineAsmHasSideEffects(LLVMValueRef Val);

LLVMBool LLVMInlineAsmIsAlignStack(LLVMValueRef Val);

unsigned LLVMInlineAsmGetDialect(LLVMValueRef Val);

LLVMConstantClass LLVMGetConstantClass(LLVMValueRef Val);

LLVMGlobalValueClass LLVMGetGlobalValueClass(LLVMValueRef GlobalVal);

LLVMConstantDataSequentialClass LLVMGetConstantDataSequentialClass(LLVMValueRef CDataSequential);

LLVMConstantFPClass LLVMGetConstantFPClass(LLVMValueRef C);

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

float LLVMGetFPValueFloat(LLVMValueRef C);

double LLVMGetFPValueDouble(LLVMValueRef C);

unsigned LLVMConstCompareGetPredicate(LLVMValueRef Val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LLVM_HS_CONSTANT_H */
