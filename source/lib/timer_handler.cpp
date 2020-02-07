#include "lib/timer_handler.hpp"

namespace gb_lib {

TimerHandler::TimerHandler(InterruptHandler* interruptHandler, MMU* mmu, SpeedModeHandler* speedModeHandler)
{
    this->interruptHandler = interruptHandler;
    this->mmu = mmu;
    this->speedModeHandler = speedModeHandler;
}

// this->speedModeHandler->requestInterrupt(Interrupt::TIMER);

void TimerHandler::updateTimers(uint32_t consumedCpuCycle)
{
    //
}

bool TimerHandler::isTimerEnabled()
{
    return BitUtil::getBit(this->mmu->getByte(TAC), 2);
}

uint8_t TimerHandler::getTimerModulo()
{
    return this->mmu->getByte(TMA);
}

uint32_t TimerHandler::getFrequency()
{
    uint32_t timerFrequency = this->timerFrequencies[(this->mmu->getByte(TAC) & 3)];

    uint32_t clockSpeed = this->normalClockSpeed * static_cast<uint32_t>(this->speedModeHandler->getSpeedMode());

    return clockSpeed / timerFrequency;
}

}
