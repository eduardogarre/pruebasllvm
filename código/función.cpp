#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include <string>
#include <vector>

extern llvm::LLVMContext contextoLlvm;
extern std::unique_ptr<llvm::Module> móduloLlvm;
extern llvm::IRBuilder<> constructorLlvm;

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




void cierraFunción(llvm::Function* función, llvm::Value* resultado)
{
    // La función debe terminar con una instrucción de retorno
    constructorLlvm.CreateRet(resultado);
    
    // Cierro el cuerpo de la función
    llvm::verifyFunction(*función);
}