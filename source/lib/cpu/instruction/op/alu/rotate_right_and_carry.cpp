#include "lib/cpu/instruction/op/alu/rotate_right_and_carry.hpp"

namespace gb_lib {

int32_t RotateRightAndCarry::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    context = context & 0xFF;

    int32_t result = context >> 1;
    result = result | (flags.isCarry() ? 0x80 : 0);

    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry((context & 1) != 0);

    return result;
}

}
