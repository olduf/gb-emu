#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include <cstdint>

#include "lib/cpu/interrupt_handler.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/mmu.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class TimerHandler
{
public:
    TimerHandler(InterruptHandler* interruptHandler, MemorySpace* mmu, bool isCGB);

    void updateTimers(uint32_t consumedCpuCycle);

private:
    InterruptHandler* interruptHandler;
    MemorySpace* mmu;
    uint32_t internalDivCounter;
    uint32_t internalTimerCounter;

private:
    bool isTimerEnabled();
    uint32_t getTimerFrequency();
    void handleDivider(uint32_t consumedCpuCycle);

private:
    const uint32_t timerFrequencies[4] = { 1024, 16, 64, 256 };
};

}

#endif

// TODO - Need to handle speed mode?
