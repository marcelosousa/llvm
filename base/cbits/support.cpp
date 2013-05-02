#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "hs_llvm_config.h"

#include "llvm-c/Core.h"
#include "llvm/PassManager.h"
#if HS_LLVM_VERSION >= 300
# include "llvm/DefaultPasses.h"
# include "llvm/Transforms/IPO/PassManagerBuilder.h"
# include "llvm/Transforms/IPO.h"
#else
# include "llvm/Support/StandardPasses.h"
#endif

#include "support.h"
#include "llvm/IR/Module.h"

using namespace llvm;

const char *LLVMGetModuleIdentifier(LLVMModuleRef M){
  return unwrap(M)->getModuleIdentifier().c_str();
}
