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

    std::cout << "defineFunción() 1" << std::endl;

    función = declaraFunción(nombre);
    
    std::cout << "defineFunción() 2" << std::endl;

    if(!función)
    {
        std::cout << "Error: la función " << nombre << "() no está declarada." << std::endl;
        return nullptr;
    }

    std::cout << "defineFunción() 3" << std::endl;

    if(!(función->empty()))
    {
        std::cout << "Error: la función " << nombre << "() ya está definida." << std::endl;
        return nullptr;
    }

    std::cout << "defineFunción() 4" << std::endl;

    llvm::BasicBlock *bloque = llvm::BasicBlock::Create(contextoLlvm, "entrada", función);
    
    std::cout << "defineFunción() 5" << std::endl;

    constructorLlvm.SetInsertPoint(bloque);

    std::cout << "defineFunción() 6" << std::endl;

    constructorLlvm.CreateRet(creaLiteralEntero(42, 32));

    std::cout << "defineFunción() 7" << std::endl;

    try
    {
        llvm::verifyFunction(*función);
    }
    catch(...)
    {
        std::cout << "Me han lanzado una excepción rara" << std::endl;
    }

    std::cout << "defineFunción() 8" << std::endl;

    return función;
}

int main(int argc, char** argv)
{
    std::cout << "¡Hola, mundo!" << std::endl;

    módulo = std::make_unique<llvm::Module>("Mi JAT", contextoLlvm);

/*
    std::cout << "0" << std::endl;
    llvm::Value* uno = creaLiteralReal(1.0);
    std::cout << "1" << std::endl;
    llvm::Value* dos = creaLiteralReal(2.0);
    std::cout << "2" << std::endl;
    llvm::Value* res = creaSumaReales(uno, dos);
    std::cout << "3" << std::endl;

    llvm::Value* tres = creaLiteralEntero(51);
    std::cout << "4" << std::endl;
*/

    llvm::Function* fnInicio = declaraFunción("inicio");
    std::cout << "5" << std::endl;
    defineFunción("inicio");
    std::cout << "6" << std::endl;
    std::vector<llvm::Value*> argumentos;
    std::cout << "7" << std::endl;
    //argumentos.push_back(tres);
    std::cout << "8" << std::endl;

    return 0;
}