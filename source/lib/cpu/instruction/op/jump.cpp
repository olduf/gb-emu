#include "lib/cpu/instruction/op/jump.hpp"

namespace gb_lib {

int32_t Jump::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    registers->setPC(static_cast<uint16_t>(context & 0xFFFF));

    return context;
}

}
