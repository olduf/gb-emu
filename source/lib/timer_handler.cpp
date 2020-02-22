#include "lib/timer_handler.hpp"

namespace gb_lib {

TimerHandler::TimerHandler(InterruptHandler* interruptHandler, MemorySpace* mmu, SpeedModeHandler* speedModeHandler)
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

uint32_t TimerHandler::getTimerFrequency()
{
    return this->timerFrequencies[(this->mmu->getByte(TAC) & 3)] * static_cast<uint32_t>(this->speedModeHandler->getSpeedMode());
}

void TimerHandler::handleDivider(uint32_t consumedCpuCycle)
{
    uint32_t dividerValue = static_cast<uint32_t>(this->mmu->getByte(DIV));
}

}
