#include "llvm/IR/Function.h"

template <typename T> llvm::Function* declaraFunción(std::string nombre);
void cierraFunción(llvm::Function* función, llvm::Value* resultado);

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