#include "lib/memory/mmu.hpp"

namespace gb_lib {

MMU::MMU(MemorySpace* cartridge, MemorySpace* ioRegisters, MemorySpace* oam, MemorySpace* videoRam, MemorySpace* workingRam)
{
    this->cartridge = cartridge;
    this->ioRegisters = ioRegisters;
    this->oam = oam;
    this->videoRam = videoRam;
    this->workingRam = workingRam;
}

MMU::~MMU()
{
    delete this->cartridge;
    this->cartridge = nullptr;

    delete this->ioRegisters;
    this->ioRegisters = nullptr;

    delete this->oam;
    this->oam = nullptr;

    delete this->videoRam;
    this->videoRam = nullptr;

    delete this->workingRam;
    this->workingRam = nullptr;
}

uint8_t MMU::getByte(uint16_t address)
{
    switch (address & 0xF000) {
      // cartridge
      case 0x0000:
      case 0x1000:
      case 0x2000:
      case 0x3000:
      case 0x4000:
      case 0x5000:
      case 0x6000:
      case 0x7000:
      case 0xA000:
      case 0xB000:
          return this->cartridge->getByte(address);
      // VRAM
      case 0x8000:
      case 0x9000:
          return this->videoRam->getByte(address);
      // GameBoy working ram
      case 0xC000:
      case 0xD000:
          return this->workingRam->getByte(address);
      // ECHO ram (redirects to 0xC000 - 0xDDFF)
      case 0xE000:
          return this->workingRam->getByte(address - 0x2000);
      case 0xF000:
          switch (address & 0xFF00)
          {
            case 0xF000:
            case 0xF100:
            case 0xF200:
            case 0xF300:
            case 0xF400:
            case 0xF500:
            case 0xF600:
            case 0xF700:
            case 0xF800:
            case 0xF900:
            case 0xFA00:
            case 0xFB00:
            case 0xFC00:
            case 0xFD00:
                // ECHO ram (redirects to 0xC000 - 0xDDFF)
                return this->workingRam->getByte(address - 0x2000);
            case 0xFE00:
                if (address < 0xFEA0)
                {
                    // OAM
                    return this->oam->getByte(address);
                }

                return 0;
            case 0xFF00:
                if (address < 0xFF80)
                {
                    return this->ioRegisters->getByte(address); // I/O Registers
                }
                else
                {
                    return this->highRAM[address - 0xFF80]; // High RAM and Interrupts Enable Register (0xFFFF)
                }
          }
    }

    return 0;
}

void MMU::setByte(uint16_t address, uint8_t value)
{
    switch (address & 0xF000) {
        // cartridge
        case 0x0000:
        case 0x1000:
        case 0x2000:
        case 0x3000:
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
        case 0xA000:
        case 0xB000:
            this->cartridge->setByte(address, value);
            break;
        // VRAM
        case 0x8000:
        case 0x9000:
            this->videoRam->setByte(address, value);
            break;
        // GameBoy working ram
        case 0xC000:
        case 0xD000:
            this->workingRam->setByte(address, value);
            break;
        case 0xE000:
            // ECHO ram (redirects to 0xC000 - 0xDDFF)
            return this->workingRam->setByte(address - 0x2000, value);
            break;
        case 0xF000:
            switch (address & 0xFF00)
            {
              case 0xF000:
              case 0xF100:
              case 0xF200:
              case 0xF300:
              case 0xF400:
              case 0xF500:
              case 0xF600:
              case 0xF700:
              case 0xF800:
              case 0xF900:
              case 0xFA00:
              case 0xFB00:
              case 0xFC00:
              case 0xFD00:
                  // ECHO ram (redirects to 0xC000 - 0xDDFF)
                  return this->workingRam->setByte(address - 0x2000, value);
                  break;
              case 0xFE00:
                  if (address < 0xFEA0)
                  {
                      // OAM
                      return this->oam->setByte(address, value);
                  }
                  break;
              case 0xFF00:
                  if (address < 0xFF80)
                  {
                      this->ioRegisters->setByte(address, value); // I/O Registers
                  }
                  else
                  {
                      this->highRAM[address - 0xFF80] = value; // High RAM and Interrupts Enable Register (0xFFFF)
                  }
            }
    }
}

// TODO
void MMU::setByteInternal(uint16_t address, uint8_t value)
{
    if (address >= 0xFF00 || address < 0xFF80) { this->ioRegisters->setByteInternal(address, value); }
}

MemorySpace* MMU::getCartridge()
{
    return this->cartridge;
}

MemorySpace* MMU::getIORegisters()
{
    return this->ioRegisters;
}

MemorySpace* MMU::getOAM()
{
    return this->oam;
}

MemorySpace* MMU::getVideoRam()
{
    return this->videoRam;
}

MemorySpace* MMU::getWorkingRam()
{
    return this->workingRam;
}

}
