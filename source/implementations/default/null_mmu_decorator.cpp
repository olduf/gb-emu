#include "implementations/default/null_mmu_decorator.hpp"

namespace gb_lib {

uint8_t NullMMUDecorator::getByte(uint16_t address)
{
    return this->memorySpace->getByte(address);
}

uint8_t NullMMUDecorator::getByteInternal(uint16_t address)
{
    return this->memorySpace->getByteInternal(address);
}

void NullMMUDecorator::setByte(uint16_t address, uint8_t value)
{
    this->memorySpace->setByte(address, value);
}

void NullMMUDecorator::setByteInternal(uint16_t address, uint8_t value)
{
    this->memorySpace->setByteInternal(address, value);
}

}
