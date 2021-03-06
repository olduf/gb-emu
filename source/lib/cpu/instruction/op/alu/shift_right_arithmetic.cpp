#include "lib/cpu/instruction/op/alu/shift_right_arithmetic.hpp"

namespace gb_lib {

int32_t ShiftRightArithmetic::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    context = context & 0xFF;
    int32_t result = (context >> 1) | (context & 0x80);

    Flags& flags = registers->getFlags();
    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry((context & 1) != 0);

    return result;
}

}
