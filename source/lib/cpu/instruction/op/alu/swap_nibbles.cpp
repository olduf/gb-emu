#include "lib/cpu/instruction/op/alu/swap_nibbles.hpp"

namespace gb_lib {

int32_t SwapNibbles::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    uint8_t lowerNibble = context & 0x0F;
    uint8_t upperNibble = context & 0xF0;
    int32_t result = (lowerNibble << 4) | (upperNibble >> 4);

    Flags& flags = registers->getFlags();
    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry(false);

    return result;
}

}
