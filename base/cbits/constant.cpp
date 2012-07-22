#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "hs_llvm_config.h"

#include "llvm-c/Core.h"

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

LLVMConstantDataSequentialClass LLVMGetConstantDataSequentialClass(LLVMValueRef CDataSequential){
  ConstantDataSequential *CDS = dyn_cast<ConstantDataSequential>(unwrap(CDataSequential));
  assert(CDS);

  if(isa<ConstantDataArray>(CDS))
     return LLVMConstantDataArray;
  else 
     return LLVMConstantDataVector;
 
}

