#pragma once

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class UnusedMemoryFEA0_FEFF : public MemorySpace
{
public:
    uint8_t getByte(uint16_t address);
};

}
