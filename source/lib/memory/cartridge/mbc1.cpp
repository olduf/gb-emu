#include "lib/memory/cartridge/mbc1.hpp"

namespace gb_lib {

MBC1::MBC1(uint8_t* data, uint32_t ramSize, uint32_t romSize, uint32_t numberOfRomBanks)
{
    this->externalRamEnabled = false;
    this->ramMode = 0;

    this->ramBank = 0;
    this->ramSize = ramSize;

    this->numberOfRomBanks = numberOfRomBanks;
    this->romBank = 1;
    this->romSize = romSize;

    if (this->ramSize > 0)
    {
        this->ram = new uint8_t[this->ramSize];
    }

    this->rom = data;
}

MBC1::~MBC1()
{
    delete[] this->ram;

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
            {
                uint32_t actualAddress = (this->romBank - 1) * 0x4000 + address;

                if (actualAddress < this->romSize)
                {
                    return this->rom[actualAddress];
                }
                else
                {
                    return 0xFF;
                }
            }
            break;
        case 0xA000:
        case 0xB000:
            {
                uint32_t effectiveRamAddress = this->getEffectiveRamAddress(address);

                if (this->externalRamEnabled && effectiveRamAddress < this->ramSize)
                {
                    return this->ram[effectiveRamAddress];
                }
                else
                {
                    return 0xFF;
                }
            }
            break;
        default:
          return 0;
    }
}

void MBC1::setByte(uint16_t address, uint8_t value)
{
    uint8_t newBankValue;

    switch (address & 0xF000)
    {
        // ram enable
        case 0x0000:
        case 0x1000:
            {
                if ((value & 0x000F) == 0b00001010)
                {
                    this->externalRamEnabled = true;
                }
                else
                {
                    this->externalRamEnabled = false;
                }
            }
            break;

        // rom bank, lower 5 bits
        case 0x2000:
        case 0x3000:
            {
                newBankValue = value & 0b00011111;

                if ((newBankValue % 0x20) == 0)
                {
                    newBankValue += 1;
                }

                this->romBank = (this->romBank & 0b01100000) | newBankValue;
            }
            break;
        // rom bank, upper 2 bits (Bit 5-6) or ram bank (00-03h)
        case 0x4000:
        case 0x5000:
            newBankValue = value & 3;

            if (this->ramMode == 0)
            {
                this->romBank = (newBankValue << 5) | (this->romBank & 0b00011111);
            }
            else
            {
                this->ramBank = newBankValue;
            }
            break;
        // ram/rom mode selection
        case 0x6000:
        case 0x7000:
            this->ramMode = value & 1;
            break;
        // write to external ram -> TODO - battery save
        case 0xA000:
        case 0xB000:
            uint32_t effectiveRamAddress = this->getEffectiveRamAddress(address);

            if (this->externalRamEnabled && effectiveRamAddress < this->ramSize)
            {
                this->ram[effectiveRamAddress] = value;
            }
    }
}

uint32_t MBC1::getEffectiveRamAddress(uint16_t address)
{
    uint32_t effectiveRamAddress = address - 0xA000;

    if (this->ramMode == 1)
    {
        effectiveRamAddress +=  this->ramBank * 0x2000;
    }

    return effectiveRamAddress;
}

}
