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
#include "función.hpp"
#include "justoatiempo.hpp"
#include "literal.hpp"
#include "soporte.hpp"
#include "tipo.hpp"


llvm::LLVMContext contextoLlvm;
llvm::IRBuilder<> constructorLlvm(contextoLlvm);
std::unique_ptr<llvm::Module> móduloLlvm;
std::map<std::string, llvm::Value *> variables;
Ñ::ConstructorJAT* jat = nullptr;


llvm::Value* sumaEnteros(int32_t val1, int32_t val2)
{
    llvm::Value* uno = creaLiteral<int32_t>(val1);
    llvm::Value* dos = creaLiteral<int32_t>(val2);
    return constructorLlvm.CreateAdd(uno, dos);
}

llvm::Value* restaEnteros(int32_t val1, int32_t val2)
{
    llvm::Value* uno = creaLiteral<int32_t>(val1);
    llvm::Value* dos = creaLiteral<int32_t>(val2);
    return constructorLlvm.CreateSub(uno, dos);
}

llvm::Value* sumaReales(double val1, double val2)
{
    llvm::Value* valor1 = creaLiteral<double>(val1);
    llvm::Value* valor2 = creaLiteral<double>(val2);
    return constructorLlvm.CreateFAdd(valor1, valor2);
}

llvm::Value* restaReales(double val1, double val2)
{
    llvm::Value* uno = creaLiteral<double>(val1);
    llvm::Value* dos = creaLiteral<double>(val2);
    return constructorLlvm.CreateFSub(uno, dos);
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
        llvm::Value* resultado = constructorLlvm.CreateAdd(var1, var2);
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
        llvm::Value* resultado = constructorLlvm.CreateFAdd(var1, var2);
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
        llvm::Value* resultado = constructorLlvm.CreateSub(var1, var2);
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
        llvm::Value* resultado = constructorLlvm.CreateFSub(var1, var2);
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