#include "lib/memory/cgb_vram.hpp"

namespace gb_lib {

CGBVideoRam::CGBVideoRam(MemorySpace* ioRegisters)
{
    this->ioRegisters = ioRegisters;
}

uint8_t CGBVideoRam::getByte(uint16_t address)
{
    return this->vram[this->getEffectiveAddress(address)];
}

void CGBVideoRam::setByte(uint16_t address, uint8_t value)
{
    LCDStatusUtil lcdStatusUtil;

    if (lcdStatusUtil.getLCDMode(this->ioRegisters) != LCDMode::PIXEL_TRANSFER)
    {
        this->vram[this->getEffectiveAddress(address)] = value;
    }
}

uint16_t CGBVideoRam::getEffectiveAddress(uint16_t address)
{
    return (this->ioRegisters->getByte(VBK) & 1) * 0x2000 + address - 0x8000;
}

}
