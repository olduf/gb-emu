#include "lib/cpu/instruction/op/push.hpp"

namespace gb_lib {

int32_t Push::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    uint8_t lsb = context & 0x00FF;
    uint8_t msb = (context & 0xFF00) >> 8;

    registers->decrementSP();
    mmu->setByte(registers->getSP(), msb);

    registers->decrementSP();
    mmu->setByte(registers->getSP(), lsb);

    return context;
}

}
