#include "lib/cpu/instruction/op/alu/shift_left_arithmetic.hpp"

namespace gb_lib {

int32_t ShiftLeftArithmetic::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int32_t result = (context << 1) & 0xFF;

    Flags& flags = registers->getFlags();
    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry((context & 0x80) != 0);

    return result;
}

}
