#include "lib/cpu/instruction/op/alu/rotate_right.hpp"

namespace gb_lib {

int32_t RotateRight::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    context = context & 0xFF;

    int32_t result = context >> 1;

    if ((context & 1) == 1)
    {
        result = result | 0x80;
        flags.setCarry(true);
    }
    else
    {
        flags.setCarry(false);
    }

    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);

    return result;
}

}
