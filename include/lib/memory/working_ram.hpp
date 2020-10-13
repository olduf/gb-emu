#pragma once

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class WorkingRam : public MemorySpace
{
public:
    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    uint8_t ram[0x2000] = {};
};

}
