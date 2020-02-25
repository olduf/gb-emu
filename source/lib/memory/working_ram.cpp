#include "lib/memory/working_ram.hpp"

namespace gb_lib {

uint8_t WorkingRam::getByte(uint16_t address)
{
    return this->ram[address - 0xC000];
}

void WorkingRam::setByte(uint16_t address, uint8_t value)
{
    this->ram[address - 0xC000] = value;
}

}
