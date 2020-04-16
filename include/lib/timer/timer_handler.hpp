#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include <cstdint>
#include "lib/cpu/interrupt_mediator.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"
#include "lib/timer/set_tac_auditor.hpp"

namespace gb_lib {

class TimerHandler : public MemorySpace
{
public:
    TimerHandler(InterruptMediator* interruptMediator, SetTacAuditor* setTacAuditor, TimerUtil* timerUtil);

    uint8_t getByte(uint16_t address);
    uint8_t getByteInternal(uint16_t address);

    void setByte(uint16_t address, uint8_t value);
    void setByteInternal(uint16_t address, uint8_t value);

    void update(uint32_t consumedCpuCycle);

private:
    uint32_t adjustConsumedCpuCycles(uint32_t consumedCpuCycles);
    void handleTimerInternally();
    void increaseTimer();

private:
    const uint32_t instruction_duration = 12;

private:
    bool timaCircuitUp;
    bool timerWasHandledInternally;

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
