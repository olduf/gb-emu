#include "lib/timer/set_tac_auditor.hpp"

namespace gb_lib {

SetTacAuditor::SetTacAuditor(TimerUtil* timerUtil)
{
    this->timerUtil = timerUtil;
}

bool SetTacAuditor::needToIncreaseTima(uint16_t divValue, uint8_t oldTacValue, uint8_t newTacValue)
{
    bool needToIncreaseTima = false;

    bool oldTimerEnabled = this->timerUtil->isTimerEnabled(oldTacValue);
    bool newTimerEnabled = this->timerUtil->isTimerEnabled(newTacValue);

    uint32_t oldHalfTimerMask = this->timerUtil->getTimerFrequency(oldTacValue) >> 1;
    uint32_t newHalfTimerMask = this->timerUtil->getTimerFrequency(newTacValue) >> 1;

    if (oldTimerEnabled)
    {
        if (!newTimerEnabled)
        {
            needToIncreaseTima = (divValue & oldHalfTimerMask) != 0;
        }
        else
        {
            needToIncreaseTima = (divValue & oldHalfTimerMask) && ((divValue & newHalfTimerMask) == 0);
        }
    }

    return needToIncreaseTima;
}

}
