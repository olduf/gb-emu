#pragma once

#include <cstring>
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class MBC1 : public MemorySpace
{
public:
    MBC1(uint8_t* data, uint32_t ramSize, uint32_t romSize, uint32_t numberOfRomBanks);
    ~MBC1();

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    bool externalRamEnabled;
    uint32_t ramMode;

    uint32_t ramBank;
    uint32_t ramSize;

    uint32_t numberOfRomBanks;
    uint32_t romBank;
    uint32_t romSize;

    uint8_t* ram;
    uint8_t* rom;

private:
    uint32_t getEffectiveRamAddress(uint16_t address);
};

}
