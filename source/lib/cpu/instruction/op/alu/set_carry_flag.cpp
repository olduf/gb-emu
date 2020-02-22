#include "lib/cpu/instruction/op/alu/set_carry_flag.hpp"

namespace gb_lib {

int32_t SetCarryFlag::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry(true);

    return context;
}

}
