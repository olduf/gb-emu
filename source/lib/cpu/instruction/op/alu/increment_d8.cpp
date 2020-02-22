#include "lib/cpu/instruction/op/alu/increment_d8.hpp"

namespace gb_lib {

int32_t IncrementD8::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int32_t result = context + 1;

    Flags& flags = registers->getFlags();
    flags.setZero((result & 0xFF) == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry((context & 0x0F) == 0x0F);

    return result;
}

}
