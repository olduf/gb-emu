#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include <cstdint>
#include "lib/cpu/interrupt_mediator.hpp"
#include "lib/timer/set_tac_auditor.hpp"

namespace gb_lib {

class TimerHandler
{
public:
    TimerHandler(InterruptMediator* interruptMediator, SetTacAuditor* setTacAuditor, TimerUtil* timerUtil);

    uint16_t getDiv();
    void setDiv(uint16_t div);

    uint8_t getTima();
    void setTima(uint8_t tima);

    uint8_t getTma();
    void setTma(uint8_t tma);

    uint8_t getTac();
    void setTac(uint8_t tac);

    void update(uint32_t consumedCpuCycle);

private:
    uint32_t adjustConsumedCpuCycles(uint32_t consumedCpuCycles);
    void increaseTimer();

private:
    bool divJustReset;
    bool tacJustSet;
    bool timaCircuitUp;

    InterruptMediator* interruptMediator;
    SetTacAuditor* setTacAuditor;
    TimerUtil* timerUtil;

    uint16_t div;
    uint8_t tima;
    uint8_t tma;
    uint8_t tac;
};

}

#endif
