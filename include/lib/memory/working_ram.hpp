#ifndef _MEMORY_WORKING_RAM_H_
#define _MEMORY_WORKING_RAM_H_

#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class WorkingRam : public MemorySpace
{
public:
    WorkingRam(MemorySpace* ioRegisters);

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    uint16_t getEffectiveAddress(uint16_t address);

private:
    MemorySpace* ioRegisters;
    uint8_t ram[0x8000] = {};
};

}

#endif
