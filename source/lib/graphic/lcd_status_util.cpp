#include "lib/graphic/lcd_status_util.hpp"

namespace gb_lib {

LCDMode LCDStatusUtil::getLCDMode(uint8_t stat)
{
    return static_cast<LCDMode>(stat & 3);
}
LCDMode LCDStatusUtil::getLCDMode(MemorySpace* ioRegisters)
{
    return this->getLCDMode(ioRegisters->getByte(STAT));
}

void LCDStatusUtil::setLCDMode(MemorySpace* ioRegisters, uint8_t stat, LCDMode lcdMode)
{
    ioRegisters->setByteInternal(STAT, (stat & 0xFC) | static_cast<uint8_t>(lcdMode));
}

void LCDStatusUtil::setLCDMode(MemorySpace* ioRegisters, LCDMode lcdMode)
{
    this->setLCDMode(ioRegisters, ioRegisters->getByte(STAT), lcdMode);
}

}
