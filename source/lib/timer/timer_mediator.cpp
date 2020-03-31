#include "lib/timer/timer_mediator.hpp"

namespace gb_lib {

uint16_t TimerMediator::getDivInternalCounter()
{
    return this->divInternalCounter;
}

void TimerMediator::setDivInternalCounter(uint16_t value)
{
    this->divInternalCounter = value;
}

}
