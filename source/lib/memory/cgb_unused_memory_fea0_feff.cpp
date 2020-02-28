#include "lib/memory/cgb_unused_memory_fea0_feff.hpp"

namespace gb_lib {

uint8_t CGBUnusedMemoryFEA0_FEFF::getByte(uint16_t address)
{
    return this->memory[address - 0xFEA0];
}

void CGBUnusedMemoryFEA0_FEFF::setByte(uint16_t address, uint8_t value)
{
    // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
    // 2.10. Unused Memory Area at FEA0h-FEFFh
    // Chose NOT to copy BGB behavior for now, might revisit later
    if (address >= 0xFEC0)
    {
        address = address & 0x000F;

        this->memory[0x20 | address] = value;
        this->memory[0x30 | address] = value;
        this->memory[0x40 | address] = value;
        this->memory[0x50 | address] = value;
    }
    else
    {
        this->memory[address - 0xFEA0] = value;
    }
}

}
