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

#include "consola.hpp"
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
    llvm::Function* función;
    función = declaraFunción("inicio");

    if(!función)
    {
        std::cerr << "Error: la función " << nombre << "() no se ha podido declarar." << std::endl;
    }

    if(!(función->empty()))
    {
        std::cout << "Error: la función " << nombre << "() ya está definida." << std::endl;
        return nullptr;
    }

    llvm::BasicBlock *bloque = llvm::BasicBlock::Create(contextoLlvm, "entrada", función);

    // Abro el cuerpo de la función
    constructorLlvm.SetInsertPoint(bloque);
    // INSERTA CÓDIGO A PARTIR DE AQUÍ
    
    llvm::Value* uno = creaLiteralEntero(40, 32);
    llvm::Value* dos = creaLiteralEntero(2, 32);
    llvm::Value* res = creaSuma(uno, dos);

    // La función debe terminar con una instrucción de retorno
    constructorLlvm.CreateRet(res);
    
    // NO INSERTES MÁS CÓDIGO
    // Cierro el cuerpo de la función

    llvm::verifyFunction(*función);
    
    return función;
}

int main(int argc, char** argv)
{       
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    
    if(!jat)
    {
        jat = Ñ::ConstructorJAT::Crea();

        if(!jat)
        {
            di("Error al crear el constructor JAT");
        }
    }

    móduloLlvm = std::make_unique<llvm::Module>("moduloJAT", contextoLlvm);
    
    móduloLlvm->setDataLayout(jat->leeDisposiciónDatos());

    defineFunción("inicio");

    di(ColorConsola.cianclaro);
    di("-------------------------");
    di("REPRESENTACIÓN INTERMEDIA");
    di("-------------------------");
    di(ColorConsola.predefinido);

    móduloLlvm->print(llvm::errs(), nullptr);

    di(ColorConsola.cianclaro);
    di("-------------------------");
    di("- CONTENIDOS DEL MÓDULO -");
    di("-------------------------");
    di(ColorConsola.predefinido);
    
    jat->añadeMódulo(std::move(móduloLlvm));

    jat->muestraSímbolos();

    di(ColorConsola.cianclaro);
    di("-------------------------");
    di("------- RESULTADO -------");
    di("-------------------------");
    di(ColorConsola.predefinido);

    // Busco el símbolo "inicio" en el constructor JAT
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloInicio = jat->busca("inicio");

    int (*punteroFunción)() = (int (*)())(intptr_t)símboloInicio->getAddress();

    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "La función ");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "'");
    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "i32");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, " inicio");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "()'");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, " ha devuelto ");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "'");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", punteroFunción());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "'");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n\n");

    return 0;
}