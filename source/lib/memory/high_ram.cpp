#include "lib/memory/high_ram.hpp"

namespace gb_lib {

uint8_t HighRam::getByte(uint16_t address)
{
    return this->highRam[address - 0xFF80];
}

void HighRam::setByte(uint16_t address, uint8_t value)
{
    this->highRam[address - 0xFF80] = value;
}

}
