#include "lib/cpu/instruction/op/scalar.hpp"

namespace gb_lib {

Scalar::Scalar(uint32_t value)
{
    this->value = value;
}

int32_t Scalar::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    return this->value;
}

}
