#ifndef _MEMORY_HIGH_RAM_H_
#define _MEMORY_HIGH_RAM_H_

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class HighRam : public MemorySpace
{
public:

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    uint8_t highRam[0x8F] = {};
};

}

#endif
