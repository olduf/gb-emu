#include "lib/cpu/instruction/op/alu/complement.hpp"

namespace gb_lib {

int32_t Complement::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();
    flags.setSubtraction(false);
    flags.setHalfCarry(false);

    return ~context;
}

}
