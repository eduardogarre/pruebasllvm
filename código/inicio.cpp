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

llvm::Value* creaSumaEnteros(llvm::Value* valor1, llvm::Value* valor2)
{
    return constructorLlvm.CreateAdd(valor1, valor2);
}

llvm::Value* creaRestaEnteros(llvm::Value* valor1, llvm::Value* valor2)
{
    return constructorLlvm.CreateSub(valor1, valor2);
}

llvm::Value* llamaFunción(llvm::Function* función, std::vector<llvm::Value*> argumentos)
{
    return constructorLlvm.CreateCall(función, argumentos);
}

llvm::Function* obténFunción(std::string nombre)
{
    return móduloLlvm->getFunction(nombre);
}

template <typename T> llvm::Function* declaraFunción(std::string nombre) { /* Sin implementación */ }

template <> llvm::Function* declaraFunción<int8_t>(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getInt8Ty(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, móduloLlvm.get());
    return función;
}

template <> llvm::Function* declaraFunción<int16_t>(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getInt16Ty(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, móduloLlvm.get());
    return función;
}

template <> llvm::Function* declaraFunción<int32_t>(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getInt32Ty(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, móduloLlvm.get());
    return función;
}

template <> llvm::Function* declaraFunción<int64_t>(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getInt64Ty(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, móduloLlvm.get());
    return función;
}

template <> llvm::Function* declaraFunción<float>(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getFloatTy(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, móduloLlvm.get());
    return función;
}

template <> llvm::Function* declaraFunción<double>(std::string nombre)
{
    std::vector<llvm::Type*> argumentos(0);
    llvm::FunctionType* firmaFunción = llvm::FunctionType::get(llvm::Type::getDoubleTy(contextoLlvm), argumentos, false);
    llvm::Function* función = llvm::Function::Create(firmaFunción, llvm::Function::ExternalLinkage, nombre, móduloLlvm.get());
    return función;
}

llvm::Value* sumaEnteros(int32_t val1, int32_t val2)
{
    llvm::Value* uno = creaLiteralEntero(val1, 32);
    llvm::Value* dos = creaLiteralEntero(val2, 32);
    return creaSumaEnteros(uno, dos);
}

llvm::Value* restaEnteros(int32_t val1, int32_t val2)
{
    llvm::Value* uno = creaLiteralEntero(val1, 32);
    llvm::Value* dos = creaLiteralEntero(val2, 32);
    return creaRestaEnteros(uno, dos);
}

llvm::Value* sumaReales(double val1, double val2)
{
    llvm::Value* uno = creaLiteralReal(val1);
    llvm::Value* dos = creaLiteralReal(val2);
    return creaSumaReales(uno, dos);
}

template <typename T> llvm::Function* defineFunción(std::string nombre)
{
    llvm::Function* función;
    función = declaraFunción<T>(nombre);

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
    
    return función;
}

void cierraFunción(llvm::Function* función, llvm::Value* resultado)
{
    // La función debe terminar con una instrucción de retorno
    constructorLlvm.CreateRet(resultado);
    
    // Cierro el cuerpo de la función
    llvm::verifyFunction(*función);
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

    // SUMA DE ENTEROS
    auto fnSumaEnteros = defineFunción<int32_t>("sumaEnteros");
    llvm::Value* resultadoSumaEnteros = sumaEnteros(40, 2);
    cierraFunción(fnSumaEnteros, resultadoSumaEnteros);

    // RESTA DE ENTEROS
    auto fnRestaEnteros = defineFunción<int32_t>("restaEnteros");
    llvm::Value* resultadoRestaEnteros = restaEnteros(44, 2);
    cierraFunción(fnRestaEnteros, resultadoRestaEnteros);
    
    // SUMA DE REALES
    auto fnSumaReales = defineFunción<double>("sumaReales");
    llvm::Value* resultadoSumaReales = sumaReales(40.0, 2.0);
    cierraFunción(fnSumaReales, resultadoSumaReales);

    di(ColorConsola.cianclaro);
    di("-------------------------------");
    di("|  REPRESENTACIÓN INTERMEDIA  |");
    di("-------------------------------");
    di(ColorConsola.predefinido);

    móduloLlvm->print(llvm::errs(), nullptr);

    di(ColorConsola.cianclaro);
    di("-------------------------------");
    di("|    CONTENIDOS DEL MÓDULO    |");
    di("-------------------------------");
    di(ColorConsola.predefinido);
    
    jat->añadeMódulo(std::move(móduloLlvm));

    jat->muestraSímbolos();

    di(ColorConsola.cianclaro);
    di("-------------------------------");
    di("|          RESULTADO          |");
    di("-------------------------------");
    di(ColorConsola.predefinido);

    // Busco los símbolos en el constructor JAT
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaEnteros = jat->busca("sumaEnteros");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloRestaEnteros = jat->busca("restaEnteros");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaReales = jat->busca("sumaReales");

    int32_t (*pSumaEnteros)() = (int32_t (*)()) ((intptr_t)(símboloSumaEnteros->getAddress()));
    int32_t (*pRestaEnteros)() = (int32_t (*)()) ((intptr_t)(símboloRestaEnteros->getAddress()));
    double (*pSumaReales)() = (double (*)()) ((intptr_t)(símboloSumaReales->getAddress()));

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "sumaEnteros()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", pSumaEnteros());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "restaEnteros()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", pRestaEnteros());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "sumaReales()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%f", pSumaReales());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    return 0;
}