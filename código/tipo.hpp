#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Type.h"

template <typename T> llvm::Type* creaTipo();

template <typename T> llvm::ArrayType* creaSerie(uint64_t elementos)
{
    return llvm::ArrayType::get(creaTipo<T>(), elementos);
}