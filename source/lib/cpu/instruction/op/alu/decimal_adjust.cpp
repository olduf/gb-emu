#include "lib/cpu/instruction/op/alu/decimal_adjust.hpp"

namespace gb_lib {

int32_t DecimalAdjust::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    uint8_t result = static_cast<uint8_t>(context);

    // after a subtraction, only adjust if (half-)carry occurred
    if (flags.isSubtraction())
    {
        if (flags.isHalfCarry())
        {
            result -= 0x06;
        }
        if (flags.isCarry())
        {
            result -= 0x60;
        }
    }
    // after an addition, adjust if (half-)carry occurred or if result is out of bounds
    else
    {
        if (flags.isHalfCarry() || (result & 0x0F) > 0x09)
        {
            result += 0x06;
        }
        if (flags.isCarry() || result > 0x99)
        {
            result += 0x60;
            flags.setCarry(true);
        }
    }

    flags.setZero(result == 0);
    flags.setHalfCarry(false);

    return static_cast<int32_t>(result);
}

}
