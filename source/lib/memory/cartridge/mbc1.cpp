#include "lib/memory/cartridge/mbc1.hpp"
#include <cstdio>

namespace gb_lib {

MBC1::MBC1(uint8_t* data, uint32_t ramSize, uint32_t romSize, uint32_t numberOfRamBanks, uint32_t numberOfRomBanks)
{
    // printf("ramSize: %u romSize: %u, numberOfRamBanks: %u, numberOfRomBanks: %u\n", ramSize, romSize, numberOfRamBanks, numberOfRomBanks);
    this->externalRamEnabled = false;
    this->memoryModel = 0;

    this->numberOfRamBanks = numberOfRamBanks & 3;
    this->ramBank = 0;
    this->ramSize = ramSize;

    this->numberOfRomBanks = numberOfRomBanks;
    this->romBank = 1;
    this->romSize = romSize;

    this->ram = new uint8_t[numberOfRamBanks * 0x2000];
    this->rom = new uint8_t[numberOfRomBanks * 0x4000];

    memcpy(this->rom, data, romSize);
}

MBC1::~MBC1()
{
    delete[] this->ram;
    delete[] this->rom;

    this->ram = nullptr;
    this->rom = nullptr;
}

uint8_t MBC1::getByte(uint16_t address)
{
    switch (address & 0xF000)
    {
        case 0x0000:
        case 0x1000:
        case 0x2000:
        case 0x3000:
            return this->rom[address];
            break;
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return this->rom[(this->romBank - 1) * 0x4000 + address];
            break;
        case 0xA000:
        case 0xB000:
            if (this->externalRamEnabled && (address - 0xA000) < this->ramSize)
            {
                return this->ram[this->getEffectiveRamAddress(address)];
            }
            else
            {
                return 0xFF;
            }
            break;
        default:
          return 0;
    }
}

void MBC1::setByte(uint16_t address, uint8_t value)
{
    // printf("writing value 0x%02X to 0x%04X, memory model: %u\n", value, address, this->memoryModel);
    uint8_t newBankValue;

    switch (address & 0xF000)
    {
        case 0x0000:
        case 0x1000:
            if ((value & 0x00FF) == 0x0A)
            {
                this->externalRamEnabled = true;
            }
            else
            {
                this->externalRamEnabled = false;
            }

            break;

        // rom bank, lower 5 bits
        case 0x2000:
        case 0x3000:
            newBankValue = value & 0x1F;

            if ((newBankValue % 0x20) == 0)
            {
                newBankValue += 1;
            }

            if (this->memoryModel == 0)
            {
                this->romBank = ((this->romBank & 0x60) | newBankValue) % this->numberOfRomBanks;
            }
            else
            {
                this->romBank = newBankValue % this->numberOfRomBanks;
            }
            break;
        // rom bank, upper 2 bits or ram bank
        case 0x4000:
        case 0x5000:
            newBankValue = value & 3;

            if (this->memoryModel == 0)
            {
                this->romBank = ((newBankValue << 5) | (this->romBank & 0x1F)) % this->numberOfRomBanks;
            }
            else
            {
                this->ramBank = newBankValue % this->numberOfRamBanks;
            }
            break;
        // ram/rom mode selection
        case 0x6000:
        case 0x7000:
            this->memoryModel = value & 1;
            break;
        // write to external ram -> TODO - battery save
        case 0xA000:
        case 0xB000:
            if (this->externalRamEnabled && (address - 0xA000) < this->ramSize)
            {
                this->ram[this->getEffectiveRamAddress(address)] = value;
            }
    }
}

uint16_t MBC1::getEffectiveRamAddress(uint16_t address)
{
    uint16_t effectiveRamAddress = address - 0xA000;

    if (this->memoryModel == 1)
    {
        effectiveRamAddress +=  this->ramBank * 0x2000;
    }

    return effectiveRamAddress;
}

}
