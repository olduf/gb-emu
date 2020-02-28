#include "lib/memory/memory_space.hpp"

namespace gb_lib {

uint8_t MemorySpace::getByteInternal(uint16_t address)
{
    return this->getByte(address);
}

void MemorySpace::setByte(uint16_t address, uint8_t value) {}

void MemorySpace::setByteInternal(uint16_t address, uint8_t value)
{
    this->setByte(address, value);
}

}
