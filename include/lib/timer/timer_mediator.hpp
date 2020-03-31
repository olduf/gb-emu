#ifndef _TIMER_MEDIATOR_H_
#define _TIMER_MEDIATOR_H_

#include <cstdint>

namespace gb_lib {

class TimerMediator
{
public:
    uint16_t getDivInternalCounter();
    void setDivInternalCounter(uint16_t value);

    uint16_t getTimerInternalCounter();
    void setTimerInternalCounter(uint16_t value);

    void increaseCounters(uint32_t value);
    void reset();

private:
    uint16_t divInternalCounter = 0;
    uint16_t timerInternalCounter = 0;
};

}

#endif
