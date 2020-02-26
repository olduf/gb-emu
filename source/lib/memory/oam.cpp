#include "lib/memory/oam.hpp"

namespace gb_lib {

OAM::OAM(MemorySpace* ioRegisters)
{
    this->ioRegisters = ioRegisters;
}

uint8_t OAM::getByte(uint16_t address)
{
    return this->oam[address - 0xFE00];
}

void OAM::setByte(uint16_t address, uint8_t value)
{
    LCDStatusUtil lcdStatusUtil;
    LCDMode lcdMode = lcdStatusUtil.getLCDMode(this->ioRegisters);

    if (lcdMode != LCDMode::OAM_SEARCH && lcdMode != LCDMode::PIXEL_TRANSFER)
    {
        this->oam[address - 0xFE00] = value;
    }
}

}
