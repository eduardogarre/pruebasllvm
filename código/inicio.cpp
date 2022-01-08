#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

static llvm::LLVMContext contextoLlvm;
static llvm::IRBuilder<> constructorLlvm(contextoLlvm);
static std::unique_ptr<llvm::Module> módulo;
static std::map<std::string, llvm::Value *> variables;

int main(int argc, char** argv)
{
    std::cout << "¡Hola, mundo!" << std::endl;

    return 0;
}