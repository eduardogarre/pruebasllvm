#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

extern llvm::LLVMContext contextoLlvm;

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