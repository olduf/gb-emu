#include "lib/memory/working_ram.hpp"

namespace gb_lib {

WorkingRam::WorkingRam(MemorySpace* ioRegisters)
{
    this->ioRegisters = ioRegisters;
}

uint8_t WorkingRam::getByte(uint16_t address)
{
    return this->ram[this->getEffectiveAddress(address)];
}

void WorkingRam::setByte(uint16_t address, uint8_t value)
{
    this->ram[this->getEffectiveAddress(address)] = value;
}

uint16_t WorkingRam::getEffectiveAddress(uint16_t address)
{
    uint16_t effectiveAddress = address - 0xC000;

    if (address < 0xD000)
    {
        return effectiveAddress;
    }
    else
    {
        uint8_t sbvk = this->ioRegisters->getByte(SBVK) & 7;
        if (sbvk == 0)
        {
            sbvk = 1;
        }

        return (sbvk - 1) * 0x1000 + effectiveAddress;
    }
}

}
