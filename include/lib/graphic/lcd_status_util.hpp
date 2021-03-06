#pragma once

#include "lib/graphic/lcd_mode.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class LCDStatusUtil
{
public:
    LCDMode getLCDMode(uint8_t stat);
    LCDMode getLCDMode(MemorySpace* ioRegisters);
    void setLCDMode(MemorySpace* ioRegisters, uint8_t stat, LCDMode lcdMode);
    void setLCDMode(MemorySpace* ioRegisters, LCDMode lcdMode);
};

}
