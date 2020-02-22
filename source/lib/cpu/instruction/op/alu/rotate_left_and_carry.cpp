#include "lib/cpu/instruction/op/alu/rotate_left_and_carry.hpp"

namespace gb_lib {

int32_t RotateLeftAndCarry::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();

    int32_t result = (context << 1) & 0xFF;
    result = result | (flags.isCarry() ? 1 : 0);

    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry((context & 0x80) != 0);

    return result;
}

}
