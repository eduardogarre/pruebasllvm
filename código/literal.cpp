#include "llvm/IR/Constants.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Value.h"

extern llvm::LLVMContext contextoLlvm;

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