#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"

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

template <> llvm::Type* creaTipo<bool*>()
{
    return llvm::PointerType::getUnqual(creaTipo<bool>());
}

template <> llvm::Type* creaTipo<int8_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<int8_t>());
}

template <> llvm::Type* creaTipo<uint8_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<uint8_t>());
}

template <> llvm::Type* creaTipo<int16_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<int16_t>());
}

template <> llvm::Type* creaTipo<uint16_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<uint16_t>());
}

template <> llvm::Type* creaTipo<int32_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<int32_t>());
}

template <> llvm::Type* creaTipo<uint32_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<uint32_t>());
}

template <> llvm::Type* creaTipo<int64_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<int64_t>());
}

template <> llvm::Type* creaTipo<uint64_t*>()
{
    return llvm::PointerType::getUnqual(creaTipo<uint64_t>());
}

template <> llvm::Type* creaTipo<float*>()
{
    return llvm::PointerType::getUnqual(creaTipo<float>());
}

template <> llvm::Type* creaTipo<double*>()
{
    return llvm::PointerType::getUnqual(creaTipo<double>());
}