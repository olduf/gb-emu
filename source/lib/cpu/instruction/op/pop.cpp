#include "lib/cpu/instruction/op/pop.hpp"

namespace gb_lib {

int32_t Pop::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    uint8_t lsb = mmu->getByte(registers->getSP());
    registers->incrementSP();

    uint8_t msb = mmu->getByte(registers->getSP());
    registers->incrementSP();

    return static_cast<uint32_t>((msb << 8) | lsb);
}

}
