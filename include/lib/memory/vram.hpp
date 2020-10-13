#pragma once

#include "lib/graphic/lcd_status_util.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class VideoRam : public MemorySpace
{
public:
    VideoRam(MemorySpace* ioRegisters);

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    MemorySpace* ioRegisters;
    uint8_t vram[0x2000] = {};
};

}
