#ifndef _TIMER_HANDLER_H_
#define _TIMER_HANDLER_H_

#include <cstdint>
#include "lib/cpu/interrupt_mediator.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class TimerHandler
{
public:
    TimerHandler(InterruptMediator* interruptMediator);

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
    bool didTimerBitChangeFromOneToZero(uint16_t divValue1, uint16_t divValue2, uint32_t timerFrequency1, uint32_t timerFrequency2);
    bool isTimerEnabled(uint8_t tac);
    bool isSelectedTimerBitUp(uint16_t divValue, uint32_t timerFrequency);

    uint32_t adjustConsumedCpuCycles(uint32_t consumedCpuCycles);
    uint32_t getTimerFrequency(uint8_t tac);

    void handleSetTacGlitch(uint8_t newTac);
    void increaseTimer();

private:
    bool divGotReset;
    InterruptMediator* interruptMediator;
    uint16_t div;
    uint8_t tima;
    uint8_t tma;
    uint8_t tac;

private:
    const uint32_t timerFrequencies[4] = { 1024, 16, 64, 256 };
    const uint16_t timerIncreaseMask = 0x02A8; // 0b0000001010101000
};

}

#endif
