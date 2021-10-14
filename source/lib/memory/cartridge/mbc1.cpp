#include "lib/memory/cartridge/mbc1.hpp"

namespace gb_lib {

MBC1::MBC1(uint8_t* data, uint32_t ramSize, uint32_t romSize)
{
    this->ram = nullptr;
    this->rom = data;

    this->bankingMode = BankingMode::SIMPLE;
    this->externalRamEnabled = false;

    this->currentRamBank = 0;
    this->effectiveRamBank = 0;
    this->numberOfRamBanks = ramSize / 0x2000;
    this->ramSize = ramSize;

    this->currentRomBank = 1;
    this->effectiveRomBank0000 = 0;
    this->effectiveRomBank4000 = 0;
    this->numberOfRomBanks = romSize / 0x4000;
    this->romSize = romSize;

    if (ramSize > 0)
    {
        this->ram = new uint8_t[ramSize] {};
    }
}

MBC1::~MBC1()
{
    if (this->ram != nullptr)
    {
        delete[] this->ram;
        this->ram = nullptr;
    }

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
            return this->rom[this->effectiveRomBank0000 * 0x4000 + address];
            break;
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return this->rom[this->effectiveRomBank4000 * 0x4000 + address];
            break;
        case 0xA000:
        case 0xB000:
            {
                uint32_t effectiveRamAddress = this->getEffectiveRAMAddress(address);

                if (this->externalRamEnabled && effectiveRamAddress < this->ramSize)
                {
                    return this->ram[effectiveRamAddress];
                }

                return 0xFF;
            }
            break;
        default:
          return 0;
    }
}

void MBC1::setByte(uint16_t address, uint8_t value)
{
    switch (address & 0xF000)
    {
        case 0x0000:
        case 0x1000:
            {
                bool oldValue = this->externalRamEnabled;

                this->externalRamEnabled = (value & 0x0F) == 0x0A;

//              if (oldValue && !this->externalRamEnabled)
//              {
//                  // save battery
//              }
            }
            break;
        case 0x2000:
        case 0x3000:
            {
                this->currentRomBank = value & 0b11111;

                if (this->currentRomBank == 0)
                {
                    this->currentRomBank++;
                }

                this->setEffectiveBanks();
            }
            break;
        case 0x4000:
        case 0x5000:
            this->currentRamBank = value & 0b11;
            this->setEffectiveBanks();
            break;
        case 0x6000:
        case 0x7000:
            this->bankingMode = static_cast<BankingMode>(value & 1);
            this->setEffectiveBanks();
            break;
        case 0xA000:
        case 0xB000:
            {
                uint16_t effectiveRamAddress = this->getEffectiveRAMAddress(address);

                if (this->externalRamEnabled && effectiveRamAddress < this->ramSize)
                {
                    this->ram[effectiveRamAddress] = value;
                }
            }
    }
}

uint32_t MBC1::getEffectiveRAMAddress(uint16_t address)
{
    return this->effectiveRamBank * 0x2000 + (address - 0xA000);
}

void MBC1::setEffectiveBanks()
{
    if (this->bankingMode == BankingMode::ADVANCED)
    {
        this->effectiveRamBank = 0;

        if (this->numberOfRamBanks > 0)
        {
            this->effectiveRamBank = this->currentRamBank % this->numberOfRamBanks;
        }

        this->effectiveRomBank0000 = 0;
        this->effectiveRomBank4000 = (this->currentRomBank % this->numberOfRomBanks) - 1;

        uint32_t upperRomBank = this->currentRamBank << 5;

        if (upperRomBank * 0x4000 < this->romSize)
        {
            this->effectiveRomBank0000 = upperRomBank | this->effectiveRomBank0000;
            this->effectiveRomBank4000 = upperRomBank | this->effectiveRomBank4000;
        }
    }
    else // BankingMode::SIMPLE
    {
        this->effectiveRamBank = 0;
        this->effectiveRomBank0000 = 0;
        this->effectiveRomBank4000 = (this->currentRomBank %this->numberOfRomBanks) - 1;
    }
}

}
