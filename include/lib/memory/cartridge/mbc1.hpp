#pragma once

#include "lib/memory/memory_space.hpp"
#include "lib/memory/cartridge/mbc1_banking_mode.hpp"

namespace gb_lib {

class MBC1 : public MemorySpace
{
public:
    MBC1(uint8_t* data, uint32_t ramSize, uint32_t romSize);
    ~MBC1();

    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    uint8_t* ram;
    uint8_t* rom;

    BankingMode bankingMode;
    bool externalRamEnabled;

    uint32_t currentRamBank;
    uint32_t effectiveRamBank;
    uint32_t numberOfRamBanks;
    uint32_t ramSize;

    uint32_t currentRomBank;
    uint32_t effectiveRomBank0000;
    uint32_t effectiveRomBank4000;
    uint32_t numberOfRomBanks;
    uint32_t romSize;

private:
    uint32_t getEffectiveRAMAddress(uint16_t address);
    void setEffectiveBanks();
};

}
