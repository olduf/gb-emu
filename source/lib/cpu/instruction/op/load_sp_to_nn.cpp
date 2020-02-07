#include "lib/cpu/instruction/op/load_sp_to_nn.hpp"

namespace gb_lib {

int32_t LoadSPToNN::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    uint16_t address = static_cast<uint16_t>(opArgument & 0xFFFF);
    uint16_t sp = registers->getSP();
    uint8_t lsb = sp & 0x00FF;
    uint8_t msb = (sp & 0xFF00) >> 8;

    mmu->setByte(address, lsb);
    mmu->setByte(address + 1, msb);

    return context;
}

}
