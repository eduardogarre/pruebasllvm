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



template <typename T> llvm::Type* creaTipo() { /* Sin implementación */ }

template <> llvm::Type* creaTipo<bool>()
{
    return llvm::Type::getInt1Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<int8_t>()
{
    return llvm::Type::getInt8Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<uint8_t>()
{
    return llvm::Type::getInt8Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<int16_t>()
{
    return llvm::Type::getInt16Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<uint16_t>()
{
    return llvm::Type::getInt16Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<int32_t>()
{
    return llvm::Type::getInt32Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<uint32_t>()
{
    return llvm::Type::getInt32Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<int64_t>()
{
    return llvm::Type::getInt64Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<uint64_t>()
{
    return llvm::Type::getInt64Ty(contextoLlvm);
}

template <> llvm::Type* creaTipo<float>()
{
    return llvm::Type::getFloatTy(contextoLlvm);
}

template <> llvm::Type* creaTipo<double>()
{
    return llvm::Type::getDoubleTy(contextoLlvm);
}



template <typename T> llvm::Value* creaLiteral(T valor) { /* Sin implementación */ }

template <> llvm::Value* creaLiteral<float>(float valor)
{
    return llvm::ConstantFP::get(contextoLlvm, llvm::APFloat(valor));
}

template <> llvm::Value* creaLiteral<double>(double valor)
{
    return llvm::ConstantFP::get(contextoLlvm, llvm::APFloat(valor));
}

template <> llvm::Value* creaLiteral<bool>(bool valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(1, valor));
}

template <> llvm::Value* creaLiteral<int8_t>(int8_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(8, valor));
}

template <> llvm::Value* creaLiteral<uint8_t>(uint8_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(8, valor));
}

template <> llvm::Value* creaLiteral<int16_t>(int16_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(16, valor));
}

template <> llvm::Value* creaLiteral<uint16_t>(uint16_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(16, valor));
}

template <> llvm::Value* creaLiteral<int32_t>(int32_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(32, valor));
}

template <> llvm::Value* creaLiteral<uint32_t>(uint32_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(32, valor));
}

template <> llvm::Value* creaLiteral<int64_t>(int64_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(64, valor));
}

template <> llvm::Value* creaLiteral<uint64_t>(uint64_t valor)
{
    return llvm::ConstantInt::get(contextoLlvm, llvm::APInt(64, valor));
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
    llvm::Value* uno = creaLiteral<int32_t>(val1);
    llvm::Value* dos = creaLiteral<int32_t>(val2);
    return creaSumaEnteros(uno, dos);
}

llvm::Value* restaEnteros(int32_t val1, int32_t val2)
{
    llvm::Value* uno = creaLiteral<int32_t>(val1);
    llvm::Value* dos = creaLiteral<int32_t>(val2);
    return creaRestaEnteros(uno, dos);
}

llvm::Value* sumaReales(double val1, double val2)
{
    llvm::Value* uno = creaLiteral<double>(val1);
    llvm::Value* dos = creaLiteral<double>(val2);
    return creaSumaReales(uno, dos);
}

llvm::Value* restaReales(double val1, double val2)
{
    llvm::Value* uno = creaLiteral<double>(val1);
    llvm::Value* dos = creaLiteral<double>(val2);
    return creaRestaReales(uno, dos);
}

llvm::Value* creaVariable(llvm::Type* tipo, std::string nombre)
{
    return constructorLlvm.CreateAlloca(tipo, nullptr, nombre);
}

void ponEnVariable(llvm::Value* variable, llvm::Value* valor)
{
    constructorLlvm.CreateStore(valor, variable, false);
}

llvm::Value* leeVariable(llvm::Value* variable)
{
    return constructorLlvm.CreateLoad(variable);
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

    { // SUMA LITERALES ENTEROS
        auto función = defineFunción<int32_t>("sumaLiteralesEnteros");
        llvm::Value* resultado = sumaEnteros(40, 2);
        cierraFunción(función, resultado);
    }
    
    { // SUMA LITERALES REALES
        auto función = defineFunción<double>("sumaLiteralesReales");
        llvm::Value* resultado = sumaReales(40.5, 1.5);
        cierraFunción(función, resultado);
    }

    { // RESTA LITERALES ENTEROS
        auto función = defineFunción<int32_t>("restaLiteralesEnteros");
        llvm::Value* resultado = restaEnteros(44, 2);
        cierraFunción(función, resultado);
    }
    
    { // RESTA LITERALES REALES
        auto función = defineFunción<double>("restaLiteralesReales");
        llvm::Value* resultado = restaReales(44.5, 2.5);
        cierraFunción(función, resultado);
    }

    { // CREA, PON Y LEE VARIABLE ENTERA
        auto función = defineFunción<int32_t>("variableEntera");
        llvm::Value* variable = creaVariable(creaTipo<int32_t>(), "variable");
        ponEnVariable(variable, creaLiteral<int32_t>(42));
        llvm::Value* resultado = leeVariable(variable);
        cierraFunción(función, resultado);
    }

    { // CREA, PON Y LEE VARIABLE REAL
        auto función = defineFunción<double>("variableReal");
        llvm::Value* variable = creaVariable(creaTipo<double>(), "variable");
        ponEnVariable(variable, creaLiteral<double>(42.0));
        llvm::Value* resultado = leeVariable(variable);
        cierraFunción(función, resultado);
    }

    { // SUMA VARIABLES ENTERAS
        auto función = defineFunción<int32_t>("sumaVariablesEnteras");
        llvm::Value* variable1 = creaVariable(creaTipo<int32_t>(), "variable1");
        llvm::Value* variable2 = creaVariable(creaTipo<int32_t>(), "variable2");
        ponEnVariable(variable1, creaLiteral<int32_t>(4));
        ponEnVariable(variable2, creaLiteral<int32_t>(38));
        llvm::Value* var1 = leeVariable(variable1);
        llvm::Value* var2 = leeVariable(variable2);
        llvm::Value* resultado = creaSumaEnteros(var1, var2);
        cierraFunción(función, resultado);
    }

    { // SUMA VARIABLES REALES
        auto función = defineFunción<double>("sumaVariablesReales");
        llvm::Value* variable1 = creaVariable(creaTipo<double>(), "variable1");
        llvm::Value* variable2 = creaVariable(creaTipo<double>(), "variable2");
        ponEnVariable(variable1, creaLiteral<double>(40.25));
        ponEnVariable(variable2, creaLiteral<double>(1.75));
        llvm::Value* var1 = leeVariable(variable1);
        llvm::Value* var2 = leeVariable(variable2);
        llvm::Value* resultado = creaSumaReales(var1, var2);
        cierraFunción(función, resultado);
    }

    { // RESTA VARIABLES ENTERAS
        auto función = defineFunción<int32_t>("restaVariablesEnteras");
        llvm::Value* variable1 = creaVariable(creaTipo<int32_t>(), "variable1");
        llvm::Value* variable2 = creaVariable(creaTipo<int32_t>(), "variable2");
        ponEnVariable(variable1, creaLiteral<int32_t>(48));
        ponEnVariable(variable2, creaLiteral<int32_t>(6));
        llvm::Value* var1 = leeVariable(variable1);
        llvm::Value* var2 = leeVariable(variable2);
        llvm::Value* resultado = creaRestaEnteros(var1, var2);
        cierraFunción(función, resultado);
    }

    { // RESTA VARIABLES REALES
        auto función = defineFunción<double>("restaVariablesReales");
        llvm::Value* variable1 = creaVariable(creaTipo<double>(), "variable1");
        llvm::Value* variable2 = creaVariable(creaTipo<double>(), "variable2");
        ponEnVariable(variable1, creaLiteral<double>(46.5));
        ponEnVariable(variable2, creaLiteral<double>(4.5));
        llvm::Value* var1 = leeVariable(variable1);
        llvm::Value* var2 = leeVariable(variable2);
        llvm::Value* resultado = creaRestaReales(var1, var2);
        cierraFunción(función, resultado);
    }

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
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaLiteralesEnteros    = jat->busca("sumaLiteralesEnteros");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaLiteralesReales     = jat->busca("sumaLiteralesReales");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloRestaLiteralesEnteros   = jat->busca("restaLiteralesEnteros");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloRestaLiteralesReales    = jat->busca("restaLiteralesReales");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloVariableEntera          = jat->busca("variableEntera");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloVariableReal            = jat->busca("variableReal");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaVariablesEnteras    = jat->busca("sumaVariablesEnteras");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloSumaVariablesReales     = jat->busca("sumaVariablesReales");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloRestaVariablesEnteras   = jat->busca("restaVariablesEnteras");
    llvm::Expected<llvm::JITEvaluatedSymbol> símboloRestaVariablesReales    = jat->busca("restaVariablesReales");

    // Obtengo punteros a las funciones construidas
    int32_t (*pSumaLiteralesEnteros)()      = (int32_t  (*)()) ((intptr_t)(símboloSumaLiteralesEnteros->getAddress()));
    double  (*pSumaLiteralesReales)()       = (double   (*)()) ((intptr_t)(símboloSumaLiteralesReales->getAddress()));
    int32_t (*pRestaLiteralesEnteros)()     = (int32_t  (*)()) ((intptr_t)(símboloRestaLiteralesEnteros->getAddress()));
    double  (*pRestaLiteralesReales)()      = (double   (*)()) ((intptr_t)(símboloRestaLiteralesReales->getAddress()));
    int32_t (*pVariableEntera)()            = (int32_t  (*)()) ((intptr_t)(símboloVariableEntera->getAddress()));
    double  (*pVariableReal)()              = (double   (*)()) ((intptr_t)(símboloVariableReal->getAddress()));
    int32_t (*pSumaVariablesEnteras)()      = (int32_t  (*)()) ((intptr_t)(símboloSumaVariablesEnteras->getAddress()));
    double  (*pSumaVariablesReales)()       = (double   (*)()) ((intptr_t)(símboloSumaVariablesReales->getAddress()));
    int32_t (*pRestaVariablesEnteras)()     = (int32_t  (*)()) ((intptr_t)(símboloRestaVariablesEnteras->getAddress()));
    double  (*pRestaVariablesReales)()      = (double   (*)()) ((intptr_t)(símboloRestaVariablesReales->getAddress()));

    // Ejecuto una a una todas las funciones:
    
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

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "variableEntera()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", pVariableEntera());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "variableReal()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%f", pVariableReal());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "sumaVariablesEnteras()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", pSumaVariablesEnteras());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "sumaVariablesReales()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%f", pSumaVariablesReales());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "restaVariablesEnteras()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%d", pRestaVariablesEnteras());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    fprintf(stderr, ColorConsola.cianclaro);
    fprintf(stderr, "restaVariablesReales()");
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\t▶   ");
    fprintf(stderr, ColorConsola.amarilloclaro);
    fprintf(stderr, "%f", pRestaVariablesReales());
    fprintf(stderr, ColorConsola.predefinido);
    fprintf(stderr, "\n");

    return 0;
}