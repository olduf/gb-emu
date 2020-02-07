#include "lib/cpu/instruction/op/alu/decimal_adjust.hpp"

namespace gb_lib {

int32_t DecimalAdjust::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    int32_t result = context;


    if (flags.isSubtraction())
    {
        if (flags.isHalfCarry())
        {
            context = (context - 0x06) & 0xFF;
        }
        if (flags.isCarry())
        {
            context = (context - 0x60) & 0xFF;
        }
    }
    else
    {
        if (flags.isHalfCarry() || (result & 0x0F) > 9)
        {
            result += 0x06;
        }
        if (flags.isCarry() || result > 0x9F)
        {
            result += 0x60;
        }
    }

    if (result > 0xFF)
    {
        flags.setCarry(true);
        result = result & 0xFF;
    }

    flags.setZero(result == 0);
    flags.setHalfCarry(false);

    return result;
}

}
