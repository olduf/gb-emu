#include "lib/timer_handler.hpp"

namespace gb_lib {

TimerHandler::TimerHandler(InterruptHandler* interruptHandler, MemorySpace* mmu, bool isCGB)
{
    this->interruptHandler = interruptHandler;
    this->mmu = mmu;

    // TODO - initialize value?
    this->internalDivCounter = 0;
    this->internalTimerCounter = 0;
}

// TODO - handle obscure behavior (https://gbdev.gg8.se/wiki/articles/Timer_Obscure_Behaviour)
void TimerHandler::updateTimers(uint32_t consumedCpuCycle)
{
    this->handleDivider(consumedCpuCycle);

    if (this->isTimerEnabled())
    {
        this->internalTimerCounter += consumedCpuCycle;

        if (this->internalTimerCounter >= this->getTimerFrequency())
        {
            uint8_t timerValue = this->mmu->getByte(TIMA);

            if (timerValue == 0xFF)
            {
                this->mmu->setByte(TIMA, this->mmu->getByte(TMA));
                this->interruptHandler->requestInterrupt(Interrupt::TIMER);
            }
            else
            {
                this->mmu->setByte(TIMA, timerValue + 1);
            }
        }
    }
}

bool TimerHandler::isTimerEnabled()
{
    return BitUtil::getBit(this->mmu->getByte(TAC), 2);
}

uint32_t TimerHandler::getTimerFrequency()
{
    return this->timerFrequencies[(this->mmu->getByte(TAC) & 3)];
}

void TimerHandler::handleDivider(uint32_t consumedCpuCycle)
{
    this->internalDivCounter += consumedCpuCycle;

    if (this->internalDivCounter >= 255)
    {
        this->internalDivCounter -= 255;
        this->mmu->setByte(DIV, this->mmu->getByte(DIV) + 1);
    }
}

}
