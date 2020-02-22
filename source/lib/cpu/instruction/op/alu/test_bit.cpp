#include "lib/cpu/instruction/op/alu/test_bit.hpp"

namespace gb_lib {

TestBit::TestBit(uint8_t n)
{
    this->n = n;
}

int32_t TestBit::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    uint8_t byte = static_cast<uint8_t>(context & 0xFF);
    Flags& flags = registers->getFlags();

    flags.setZero((byte & (1 << n)) == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(true);

    return context;
}

}
