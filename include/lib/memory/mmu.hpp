#ifndef _MEMORY_MMU_H_
#define _MEMORY_MMU_H_

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class MMU : public MemorySpace
{
public:
    MMU(MemorySpace* cartridge, MemorySpace* ioRegisters, MemorySpace* oam, MemorySpace* videoRam, MemorySpace* workingRam);
    ~MMU();

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

    void setByteInternal(uint16_t address, uint8_t value);

    MemorySpace* getCartridge();
    MemorySpace* getIORegisters();
    MemorySpace* getOAM();
    MemorySpace* getVideoRam();
    MemorySpace* getWorkingRam();

private:
    MemorySpace* cartridge;
    MemorySpace* ioRegisters;
    MemorySpace* oam;
    MemorySpace* videoRam;
    MemorySpace* workingRam;
    uint8_t highRAM[0x7F] = {};
};

}

#endif
