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
#include "llvm/Support/TargetSelect.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "justoatiempo.hpp"

static llvm::LLVMContext contextoLlvm;
static llvm::IRBuilder<> constructorLlvm(contextoLlvm);
static std::unique_ptr<llvm::Module> móduloLlvm;
static std::map<std::string, llvm::Value *> variables;
static Ñ::ConstructorJAT* jat = nullptr;

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
    return móduloLlvm->getFunction(nombre);
}

llvm::Function* declaraFunción(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getInt32Ty(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, móduloLlvm.get());
    return función;
}

llvm::Function* defineFunción(std::string nombre)
{
    di("defineFunción 1");

    llvm::Function* función;

    di("defineFunción 2");
    
    función = declaraFunción("inicio");

    di("defineFunción 3");
    
    if(!función)
    {
        std::cerr << "Error: la función " << nombre << "() no se ha podido declarar." << std::endl;
    }

    di("defineFunción 4");
    
    if(!(función->empty()))
    {
        std::cout << "Error: la función " << nombre << "() ya está definida." << std::endl;
        return nullptr;
    }

    di("defineFunción 5");
    
    llvm::BasicBlock *bloque = llvm::BasicBlock::Create(contextoLlvm, "entrada", función);

    di("defineFunción 6");
    
    constructorLlvm.SetInsertPoint(bloque);
    
    di("defineFunción 7");
    
    llvm::Value* uno = creaLiteralEntero(40, 32);
    llvm::Value* dos = creaLiteralEntero(2, 32);
    llvm::Value* res = creaSuma(uno, dos);

    di("defineFunción 8");
    
    constructorLlvm.CreateRet(res);

    di("defineFunción 9");
    
    llvm::verifyFunction(*función);

    di("defineFunción 10");
    
    return función;
}

int main(int argc, char** argv)
{
    di("0");
        
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    
    di("1");
    
    if(!jat)
    {
        jat = Ñ::ConstructorJAT::Crea();

        if(!jat)
        {
            di("Error al crear el constructor JAT");
        }
    }

    di("2");

    móduloLlvm = std::make_unique<llvm::Module>("moduloJAT", contextoLlvm);
    
    di("3");
    
    móduloLlvm->setDataLayout(jat->leeDisposiciónDatos());
    
    di("4");

    defineFunción("inicio");

    di("5");

    //llvm::Function* fnInicio = declaraFunción("inicio");
    
    di("6");
    
    jat->añadeMódulo(std::move(móduloLlvm));

    di("7");

    // Busco el símbolo "inicio" en el constructor JAT
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloInicio = jat->busca("inicio");

    di("8");

    int (*punteroFunción)() = (int (*)())(intptr_t)símboloInicio->getAddress();
    
    di("9");
    
    fprintf(stderr, "Evaluado a %d\n", punteroFunción());

    di("10");

    //móduloLlvm->print(llvm::errs(), nullptr);
    jat->muestraSímbolos();

    di("11");

    return 0;
}