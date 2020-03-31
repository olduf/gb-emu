#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include "lib/cpu/interrupt_handler.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/mmu.hpp"
#include "lib/timer/timer_mediator.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class TimerHandler
{
public:
    TimerHandler(InterruptHandler* interruptHandler, MemorySpace* mmu, TimerMediator* timerMediator);

    void updateTimers(uint32_t consumedCpuCycle);

private:
    InterruptHandler* interruptHandler;
    MemorySpace* mmu;
    TimerMediator* timerMediator;
    uint16_t previousDivCounterValue;

private:
    bool isTimerEnabled();
    bool needToIncreaseTimer(uint16_t previousValue, uint16_t currentValue, uint32_t timerFrequency);

    uint32_t getTimerFrequency();

    void increaseTimer();

private:
    const uint32_t timerFrequencies[4] = { 1024, 16, 64, 256 };

    // https://gbdev.github.io/pandocs/Timer_Obscure_Behaviour.html#relation-between-timer-and-divider-register
    const uint16_t timerIncreaseMask = 0x2A8; // 0b1010101000
};

}

#endif

// TODO - Need to handle speed mode?
