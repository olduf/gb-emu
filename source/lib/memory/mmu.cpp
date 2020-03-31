#include "lib/memory/mmu.hpp"
#include <cstdio>

namespace gb_lib {

MMU::MMU(MemorySpace* cartridge, MemorySpace* highRam, MemorySpace* ioRegisters, MemorySpace* oam, MemorySpace* unusedMemoryFEA0_FEFF, MemorySpace* videoRam, MemorySpace* workingRam)
{
    this->cartridge = cartridge;
    this->highRam = highRam;
    this->ioRegisters = ioRegisters;
    this->oam = oam;
    this->unusedMemoryFEA0_FEFF = unusedMemoryFEA0_FEFF;
    this->videoRam = videoRam;
    this->workingRam = workingRam;
}

MMU::~MMU()
{
    delete this->cartridge;
    this->cartridge = nullptr;

    delete this->highRam;
    this->highRam = nullptr;

    delete this->ioRegisters;
    this->ioRegisters = nullptr;

    delete this->oam;
    this->oam = nullptr;

    delete this->unusedMemoryFEA0_FEFF;
    this->unusedMemoryFEA0_FEFF = nullptr;

    delete this->videoRam;
    this->videoRam = nullptr;

    delete this->workingRam;
    this->workingRam = nullptr;
}

uint8_t MMU::getByte(uint16_t address)
{
    return this->getMemorySpace(address)->getByte(address);
}

uint8_t MMU::getByteInternal(uint16_t address)
{
    return this->getMemorySpace(address)->getByteInternal(address);
}

void MMU::setByte(uint16_t address, uint8_t value)
{
    if (address == 0xFF02 && value == 0x81) { printf("%c", (char)this->ioRegisters->getByte(0xFF01)); }
    this->getMemorySpace(address)->setByte(address, value);
}

void MMU::setByteInternal(uint16_t address, uint8_t value)
{
    return this->getMemorySpace(address)->setByteInternal(address, value);
}

MemorySpace* MMU::getCartridge()
{
    return this->cartridge;
}

MemorySpace* MMU::getHighRam()
{
    return this->highRam;
}

MemorySpace* MMU::getIORegisters()
{
    return this->ioRegisters;
}

MemorySpace* MMU::getOAM()
{
    return this->oam;
}

MemorySpace* MMU::getUnusedMemoryFEA0_FEFF()
{
    return this->unusedMemoryFEA0_FEFF;
}

MemorySpace* MMU::getVideoRam()
{
    return this->videoRam;
}

MemorySpace* MMU::getWorkingRam()
{
    return this->workingRam;
}

MemorySpace* MMU::getMemorySpace(uint16_t& address)
{
    switch (address & 0xF000)
    {
        // cartridge
        case 0x0000:
        case 0x1000:
        case 0x2000:
        case 0x3000:
        case 0x4000:
        case 0x5000:
        case 0x6000:
        case 0x7000:
            return this->cartridge;
        // VRAM
        case 0x8000:
        case 0x9000:
            return this->videoRam;
        // external ram
        case 0xA000:
        case 0xB000:
            return this->cartridge;
        // GameBoy working ram
        case 0xC000:
        case 0xD000:
            return this->workingRam;
        // ECHO ram (redirects to 0xC000 - 0xDDFF)
        case 0xE000:
            address = address - 0x2000;
            return this->workingRam;
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
                    address = address - 0x2000;
                    return this->workingRam;
                case 0xFE00:
                    if (address < 0xFEA0)
                    {
                        // OAM
                        return this->oam;
                    }

                    // "Unused Memory" at 0xFEA0 - 0xFEFF
                    return this->unusedMemoryFEA0_FEFF;
                case 0xFF00:
                    if (address < 0xFF80)
                    {
                        // I/O Registers
                        return this->ioRegisters;
                    }
                    else
                    {
                        // High RAM and Interrupts Enable Register (0xFFFF)
                        return this->highRam;
                    }
            }
    }
}

}
