#include "lib/memory/cartridge/cartridge_factory.hpp"

namespace gb_lib {

MemorySpace* CartridgeFactory::create(uint8_t* rom, uint32_t romFileSize)
{
    MemorySpace* cartridge = nullptr;

    uint32_t numberOfRamBanks = this->getNumberOfRamBanks(rom[0x149]);
    uint32_t ramSize = numberOfRamBanks * 0x2000;

    uint32_t numberOfRomBanks = this->getNumberOfRomBanks(rom[0x148]);
    uint32_t romSize = numberOfRomBanks * 0x4000;

    if (romSize > romFileSize)
    {
        romSize = romFileSize;
    }

    switch (rom[0x0147])
    {
        // ROM ONLY
        case 0x00: cartridge = new Rom(rom, romSize); break;

        // MBC 1
        // MBC1+RAM
        // MBC1+RAM+BATTERY
        case 0x01:
        case 0x02:
        case 0x03:
            cartridge = new MBC1(rom, ramSize, romSize, numberOfRomBanks);
            break;

        // // MBC 2
        // case 0x05: ; break; // MBC2
        // case 0x06: ; break; // MBC2+BATTERY
        // case 0x08: ; break; // ROM+RAM
        // case 0x09: ; break; // ROM+RAM+BATTERY
        //
        // // MMM01?
        // case 0x0B: ; break; // MMM01
        // case 0x0C: ; break; // MMM01+RAM
        // case 0x0D: ; break; // MMM01+RAM+BATTERY
        //
        // // MBC 3
        // case 0x0F: ; break; // MBC3+TIMER+BATTERY
        // case 0x10: ; break; // MBC3+TIMER+RAM+BATTERY
        // case 0x11: ; break; // MBC3
        // case 0x12: ; break; // MBC3+RAM
        // case 0x13: ; break; // MBC3+RAM+BATTERY
        //
        // // MBC 4
        // case 0x15: ; break; // MBC4
        // case 0x16: ; break; // MBC4+RAM
        // case 0x17: ; break; // MBC4+RAM+BATTER5
        //
        // // MBC 5
        // case 0x19: ; break; // MBC5
        // case 0x1A: ; break; // MBC5+RAM
        // case 0x1B: ; break; // MBC5+RAM+BATTERY
        // case 0x1C: ; break; // MBC5+RUMBLE
        // case 0x1D: ; break; // MBC5+RUMBLE+RAM
        // case 0x1E: ; break; // MBC5+RUMBLE+RAM+BATTERY
        //
        // case 0xFC: ; break; // POCKET CAMERA
        // case 0xFD: ; break; // BANDAI TAMA5
        // case 0xFE: ; break; // HuC3
        // case 0xFF: ; break; // HuC1+RAM+BATTERY
    }

    return cartridge;
}

uint32_t CartridgeFactory::getNumberOfRamBanks(uint8_t valueInHeader)
{
    switch (valueInHeader)
    {
        case 0: return 0;
        case 1: return 1;
        case 2: return 1;
        case 3: return 4;
        case 4: return 16;
    }

    return 0;
}

uint32_t CartridgeFactory::getNumberOfRomBanks(uint8_t valueInHeader)
{
    switch (valueInHeader)
    {
        case 0: return 2;
        case 1: return 4;
        case 2: return 8;
        case 3: return 16;
        case 4: return 32;
        case 5: return 64;
        case 6: return 128;
        case 7: return 256;
        case 0x52: return 72;
        case 0x53: return 80;
        case 0x54: return 96;
    }

    return 0;
}

}
