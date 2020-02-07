#include "lib/cpu/instruction/op/alu/set_bit.hpp"

namespace gb_lib {

SetBit::SetBit(uint8_t n)
{
    this->n = n;
}

int32_t SetBit::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    return BitUtil::setBit(static_cast<uint8_t>(context), this->n);
}

}
