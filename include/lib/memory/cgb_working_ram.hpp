#pragma once

#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class CGBWorkingRam : public MemorySpace
{
public:
    CGBWorkingRam(MemorySpace* ioRegisters);

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    uint16_t getEffectiveAddress(uint16_t address);

private:
    MemorySpace* ioRegisters;
    uint8_t ram[0x8000] = {};
};

}
