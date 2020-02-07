#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include <cstdint>

#include "lib/cpu/interrupt_handler.hpp"
#include "lib/cpu/speedmode_handler.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/mmu.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class TimerHandler
{
public:
    TimerHandler(InterruptHandler* interruptHandler, MMU* mmu, SpeedModeHandler* speedModeHandler);

    void updateTimers(uint32_t consumedCpuCycle);

private:
    InterruptHandler* interruptHandler;
    MMU* mmu;
    SpeedModeHandler* speedModeHandler;

private:
    bool isTimerEnabled();
    uint8_t getTimerModulo();
    uint32_t getFrequency();

private:
    const uint32_t normalClockSpeed = 4194304;
    const uint32_t timerFrequencies[4] = { 1024, 16, 64, 256 };
};

}

#endif

// TODO - Need to handle speed mode?
