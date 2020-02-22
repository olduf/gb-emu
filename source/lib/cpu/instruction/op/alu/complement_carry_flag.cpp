#include "lib/cpu/instruction/op/alu/complement_carry_flag.hpp"

namespace gb_lib {

int32_t ComplementCarryFlag::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry(!flags.isCarry());

    return context;
}

}
