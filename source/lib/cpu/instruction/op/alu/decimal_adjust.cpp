#include "lib/cpu/instruction/op/alu/decimal_adjust.hpp"

namespace gb_lib {

int32_t DecimalAdjust::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    int32_t result = context;

    // after a subtraction, only adjust if (half-)carry occurred
    if (flags.isSubtraction())
    {
        if (flags.isHalfCarry())
        {
            result = (result - 0x06) & 0xFF;
        }
        if (flags.isCarry())
        {
            result = (result - 0x60) & 0xFF;
        }
    }
    else
    {
        if (flags.isHalfCarry() || (result & 0x0F) > 0x09)
        {
            result += 0x06;
        }
        if (flags.isCarry() || result > 0x9F)
        {
            result += 0x60;
            flags.setCarry(true);
        }
    }

    result = result & 0xFF;
    flags.setZero(result == 0);
    flags.setHalfCarry(false);

    return result;
}

}
