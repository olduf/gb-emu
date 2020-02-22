#include "lib/cpu/instruction/op/alu/reset_bit.hpp"

namespace gb_lib {

ResetBit::ResetBit(uint8_t n)
{
    this->n = n;
}

int32_t ResetBit::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    return BitUtil::setBit(static_cast<uint8_t>(context), this->n);
}

}
