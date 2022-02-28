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

llvm::Value* creaRestaReales(llvm::Value* valor1, llvm::Value* valor2)
{
    return constructorLlvm.CreateFSub(valor1, valor2);
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

llvm::Value* restaReales(double val1, double val2)
{
    llvm::Value* uno = creaLiteralReal(val1);
    llvm::Value* dos = creaLiteralReal(val2);
    return creaRestaReales(uno, dos);
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

    // SUMA LITERALES ENTEROS
    auto fnSumaEnteros = defineFunción<int32_t>("sumaLiteralesEnteros");
    llvm::Value* resultadoSumaEnteros = sumaEnteros(40, 2);
    cierraFunción(fnSumaEnteros, resultadoSumaEnteros);
    
    // SUMA LITERALES REALES
    auto fnSumaReales = defineFunción<double>("sumaLiteralesReales");
    llvm::Value* resultadoSumaReales = sumaReales(40.0, 2.0);
    cierraFunción(fnSumaReales, resultadoSumaReales);

    // RESTA LITERALES ENTEROS
    auto fnRestaEnteros = defineFunción<int32_t>("restaLiteralesEnteros");
    llvm::Value* resultadoRestaEnteros = restaEnteros(44, 2);
    cierraFunción(fnRestaEnteros, resultadoRestaEnteros);
    
    // RESTA LITERALES REALES
    auto fnRestaReales = defineFunción<double>("restaLiteralesReales");
    llvm::Value* resultadoRestaReales = restaReales(44.0, 2.0);
    cierraFunción(fnRestaReales, resultadoRestaReales);

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
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaLiteralesEnteros = jat->busca("sumaLiteralesEnteros");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaLiteralesReales = jat->busca("sumaLiteralesReales");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloRestaLiteralesEnteros = jat->busca("restaLiteralesEnteros");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloRestaLiteralesReales = jat->busca("restaLiteralesReales");

    int32_t (*pSumaLiteralesEnteros)() = (int32_t (*)()) ((intptr_t)(símboloSumaLiteralesEnteros->getAddress()));
    double (*pSumaLiteralesReales)() = (double (*)()) ((intptr_t)(símboloSumaLiteralesReales->getAddress()));
    int32_t (*pRestaLiteralesEnteros)() = (int32_t (*)()) ((intptr_t)(símboloRestaLiteralesEnteros->getAddress()));
    double (*pRestaLiteralesReales)() = (double (*)()) ((intptr_t)(símboloRestaLiteralesReales->getAddress()));

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "sumaLiteralesEnteros()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", pSumaLiteralesEnteros());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "sumaLiteralesReales()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%f", pSumaLiteralesReales());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "restaLiteralesEnteros()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", pRestaLiteralesEnteros());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "restaLiteralesReales()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%f", pRestaLiteralesReales());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    return 0;
}