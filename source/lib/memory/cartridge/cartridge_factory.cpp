#include "lib/memory/cartridge/cartridge_factory.hpp"

namespace gb_lib {

MemorySpace* CartridgeFactory::create(uint8_t* rom, uint32_t romFileSize)
{
    MemorySpace* cartridge = nullptr;

    uint32_t ramSize = this->getRamSize(rom[0x149]);
    uint32_t numberOfRamBanks = ramSize / 0x2000;
    numberOfRamBanks += (numberOfRamBanks == 0 && ramSize > 0) ? 1 : 0;

    uint32_t romSize = this->getRomSize(rom[0x148]);
    uint32_t numberOfRomBanks = romSize / 0x4000;

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
            cartridge = new MBC1(rom, ramSize, romSize, numberOfRamBanks, numberOfRomBanks);
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
        // // MBC 3
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

uint32_t CartridgeFactory::getRamSize(uint8_t valueInHeader)
{
    uint32_t ramSize = 0;

    switch (ramSize)
    {
        case 0x01: ramSize = 0x800; break;   // 2 KBytes (1 bank)
        case 0x02: ramSize = 0x2000; break;  // 8 Kbytes (1 bank)
        case 0x03: ramSize = 0x8000; break;  // 32 KBytes (4 banks of 8KBytes each)
        case 0x04: ramSize = 0x20000; break; // 128 KBytes (16 banks of 8KBytes each)
        case 0x05: ramSize = 0x10000; break; // 64 KBytes (8 banks of 8KBytes each)
    }

    return ramSize;
}

uint32_t CartridgeFactory::getRomSize(uint8_t valueInHeader)
{
  uint32_t romSize = 0x8000;

  switch (romSize)
  {
      case 0x00: romSize = 0x8000; break;   // 32 KByte (no ROM banking)
      case 0x01: romSize = 0x10000; break;  // 64 KByte (4 banks)
      case 0x02: romSize = 0x20000; break;  // 128 KByte (8 banks)
      case 0x03: romSize = 0x40000; break;  // 256 KByte (16 banks)
      case 0x04: romSize = 0x80000; break;  // 512 KByte (32 banks)
      case 0x05: romSize = 0x100000; break; // 1 MByte (64 banks)  - only 63 banks used by MBC1
      case 0x06: romSize = 0x200000; break; // 2 MByte (128 banks) - only 125 banks used by MBC1
      case 0x07: romSize = 0x400000; break; // 4 MByte ( 56 banks)
      case 0x08: romSize = 0x800000; break; // 8 MByte (512 banks)
      case 0x52: romSize = 0x120000; break; // 1.1 MByte (72 banks)
      case 0x53: romSize = 0x140000; break; // 1.2 MByte (80 banks)
      case 0x54: romSize = 0x180000; break; // 1.5 MByte (96 banks)
  }

  return romSize;
}

}
