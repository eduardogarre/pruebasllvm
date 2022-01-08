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

llvm::Type* creaTipoEntero(uint8_t dígitos)
{
    return llvm::Type::getIntNTy(contextoLlvm, dígitos);
}

llvm::Value* creaLiteralReal(double valor)
{
    return llvm::ConstantFP::get(contextoLlvm, llvm::APFloat(valor));
}

llvm::Value* creaLiteralEntero(uint64_t valor, uint8_t dígitos = 64)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(dígitos, valor));
}

llvm::Value* creaSumaReales(llvm::Value* valor1, llvm::Value* valor2)
{
    return constructorLlvm.CreateFAdd(valor1, valor2);
}

llvm::Value* creaSuma(llvm::Value* valor1, llvm::Value* valor2)
{
    return constructorLlvm.CreateAdd(valor1, valor2);
}

llvm::Value* llamaFunción(llvm::Function* función, std::vector<llvm::Value*> argumentos)
{
    return constructorLlvm.CreateCall(función, argumentos);
}

llvm::Function* obténFunción(std::string nombre)
{
    return módulo->getFunction(nombre);
}

llvm::Function* declaraFunción(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getInt32Ty(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, módulo.get());
    return función;
}

llvm::Function* defineFunción(std::string nombre)
{
    llvm::Function* función;

    función = módulo->getFunction(nombre);

    if(!función)
    {
        std::cout << "Aviso: la función " << nombre << "() no está declarada. La declaro ahora." << std::endl;
        
        función = declaraFunción("inicio");
        if(!función)
        {
            std::cerr << "Error: la función " << nombre << "() no se ha podido declarar." << std::endl;
        }
    }

    if(!(función->empty()))
    {
        std::cout << "Error: la función " << nombre << "() ya está definida." << std::endl;
        return nullptr;
    }

    llvm::BasicBlock *bloque = llvm::BasicBlock::Create(contextoLlvm, "entrada", función);

    constructorLlvm.SetInsertPoint(bloque);
    
    llvm::Value* uno = creaLiteralEntero(40, 32);
    llvm::Value* dos = creaLiteralEntero(2, 32);
    llvm::Value* res = creaSuma(uno, dos);

    constructorLlvm.CreateRet(res);

    llvm::verifyFunction(*función);

    return función;
}

int main(int argc, char** argv)
{
    módulo = std::make_unique<llvm::Module>("Mi JAT", contextoLlvm);

    llvm::Function* fnInicio = declaraFunción("inicio");
    defineFunción("inicio");

    módulo->print(llvm::errs(), nullptr);

    return 0;
}