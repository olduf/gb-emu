#include "lib/timer/timer_util.hpp"

namespace gb_lib {

bool TimerUtil::isTimerEnabled(uint8_t tac)
{
    return BitUtil::getBit(tac, 2);
}

bool TimerUtil::isTimaCircuitUp(uint16_t div, uint8_t tac)
{
    return this->isTimerEnabled(tac) && (div & (this->getTimerFrequency(tac) >> 1)) != 0;
}

uint32_t TimerUtil::getTimerFrequency(uint8_t tac)
{
    return this->timerFrequencies[tac & 0b00000011];
}

}
