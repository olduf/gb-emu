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

uint16_t TimerMediator::getTimerInternalCounter()
{
    return this->timerInternalCounter;
}

void TimerMediator::setTimerInternalCounter(uint16_t value)
{
    this->timerInternalCounter = value;
}

void TimerMediator::increaseCounters(uint32_t value)
{
    this->divInternalCounter += value;
    this->timerInternalCounter += value;
}

void TimerMediator::reset()
{
    this->divInternalCounter = 0;
    this->timerInternalCounter = 0;
}

}
