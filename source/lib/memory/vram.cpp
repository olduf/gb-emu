#include "lib/memory/vram.hpp"

namespace gb_lib {

VideoRam::VideoRam(MemorySpace* ioRegisters)
{
    this->ioRegisters = ioRegisters;
}

uint8_t VideoRam::getByte(uint16_t address)
{
    return this->vram[address - 0x8000];
}

void VideoRam::setByte(uint16_t address, uint8_t value)
{
    LCDStatusUtil lcdStatusUtil;

    if (lcdStatusUtil.getLCDMode(this->ioRegisters) != LCDMode::PIXEL_TRANSFER)
    {
        this->vram[address - 0x8000] = value;
    }
}

}
