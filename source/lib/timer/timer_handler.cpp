#include "lib/timer/timer_handler.hpp"

namespace gb_lib {

TimerHandler::TimerHandler(InterruptHandler* interruptHandler, MemorySpace* mmu, TimerMediator* timerMediator)
{
    this->interruptHandler = interruptHandler;
    this->mmu = mmu;
    this->timerMediator = timerMediator;
    this->previousDivCounterValue = 0;
}

// TODO - handle obscure behavior (https://gbdev.gg8.se/wiki/articles/Timer_Obscure_Behaviour)
void TimerHandler::updateTimers(uint32_t consumedCpuCycle)
{
    this->previousDivCounterValue = this->timerMediator->getDivInternalCounter();
    uint16_t finalDivCounterValue = this->previousDivCounterValue + consumedCpuCycle;

    this->timerMediator->setDivInternalCounter(finalDivCounterValue);
    this->mmu->setByteInternal(DIV, (finalDivCounterValue & 0xFF00) >> 8);

    if (this->isTimerEnabled())
    {
        uint32_t timerFrequency = this->getTimerFrequency();

        for (uint16_t i = 0; i < consumedCpuCycle; i++)
        {
            if (this->needToIncreaseTimer(this->previousDivCounterValue, this->previousDivCounterValue + 1, timerFrequency))
            {
                this->increaseTimer();
            }

            this->previousDivCounterValue++;
        }
    }
}

bool TimerHandler::isTimerEnabled()
{
    return BitUtil::getBit(this->mmu->getByte(TAC), 2);
}

bool TimerHandler::needToIncreaseTimer(uint16_t previousValue, uint16_t currentValue, uint32_t timerFrequency)
{
    // https://gbdev.github.io/pandocs/Timer_Obscure_Behaviour.html#relation-between-timer-and-divider-register
    // if the bit (determined by timer frequency) goes from HIGH to LOW, increase timer
    return (
        (previousValue & this->timerIncreaseMask & (timerFrequency >> 1)) != 0 &&
        (currentValue & this->timerIncreaseMask & (timerFrequency >> 1)) == 0
    );
}

uint32_t TimerHandler::getTimerFrequency()
{
    return this->timerFrequencies[(this->mmu->getByte(TAC) & 3)];
}

void TimerHandler::increaseTimer()
{
    uint8_t timerValue = this->mmu->getByte(TIMA);

    if (timerValue == 0xFF)
    {
        this->mmu->setByteInternal(TIMA, this->mmu->getByte(TMA));
        this->interruptHandler->requestInterrupt(Interrupt::TIMER);
    }
    else
    {
        this->mmu->setByte(TIMA, timerValue + 1);
    }
}

}
