#include "lib/cpu/interrupt_mediator.hpp"

namespace gb_lib {

uint8_t InterruptMediator::getIF()
{
    return this->ifValue | 0xE0;
}
void InterruptMediator::setIF(uint8_t ifValue)
{
    this->ifValue = ifValue;
}

void InterruptMediator::requestInterrupt(Interrupt interrupt)
{
    this->ifValue = BitUtil::setBit(this->ifValue, static_cast<uint8_t>(interrupt));
}

}
