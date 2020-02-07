#include "lib/cpu/instruction/op/alu/shift_right_logical.hpp"

namespace gb_lib {

int32_t ShiftRightLogical::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    context = context & 0xFF;
    int32_t result = context >> 1;

    Flags& flags = registers->getFlags();
    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry((context & 1) != 0);

    return result;
}

}
