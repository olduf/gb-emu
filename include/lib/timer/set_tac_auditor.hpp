#pragma once

#include <cstdint>
#include "lib/timer/timer_util.hpp"

namespace gb_lib {

class SetTacAuditor
{
public:
    SetTacAuditor(TimerUtil* timerUtil);

    bool needToIncreaseTima(uint16_t divValue, uint8_t oldTacValue, uint8_t newTac);

protected:
    TimerUtil* timerUtil;
};

}
