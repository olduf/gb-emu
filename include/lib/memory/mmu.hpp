#ifndef _MEMORY_MMU_H_
#define _MEMORY_MMU_H_

#include <cstdio>
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class MMU : public MemorySpace
{
public:
    MMU(MemorySpace* cartridge, MemorySpace* ioRegisters, MemorySpace* workingRam);

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

    void setByteInternal(uint16_t address, uint8_t value);

private:
    MemorySpace* cartridge;
    MemorySpace* ioRegisters;
    MemorySpace* workingRam;
    uint8_t temp[0xFFFF] = {};
};

}

#endif
