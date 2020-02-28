#ifndef _MEMORY_MMU_H_
#define _MEMORY_MMU_H_

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class MMU : public MemorySpace
{
public:
    MMU(MemorySpace* cartridge,  MemorySpace* highRam, MemorySpace* ioRegisters, MemorySpace* oam, MemorySpace* unusedMemoryFEA0_FEFF, MemorySpace* videoRam, MemorySpace* workingRam);
    ~MMU();

    uint8_t getByte(uint16_t address);
    uint8_t getByteInternal(uint16_t address);

    void setByte(uint16_t address, uint8_t value);
    void setByteInternal(uint16_t address, uint8_t value);

    MemorySpace* getCartridge();
    MemorySpace* getHighRam();
    MemorySpace* getIORegisters();
    MemorySpace* getOAM();
    MemorySpace* getUnusedMemoryFEA0_FEFF();
    MemorySpace* getVideoRam();
    MemorySpace* getWorkingRam();

private:
    MemorySpace* getMemorySpace(uint16_t& address);

private:
    MemorySpace* cartridge;
    MemorySpace* highRam;
    MemorySpace* ioRegisters;
    MemorySpace* oam;
    MemorySpace* unusedMemoryFEA0_FEFF;
    MemorySpace* videoRam;
    MemorySpace* workingRam;
};

}

#endif
