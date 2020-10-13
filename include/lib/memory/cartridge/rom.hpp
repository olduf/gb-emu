#pragma once

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class Rom : public MemorySpace
{
public:
    Rom(uint8_t* data, uint32_t size);

    uint8_t getByte(uint16_t address);

private:
    uint8_t* rom;
    uint32_t size;
};

}
