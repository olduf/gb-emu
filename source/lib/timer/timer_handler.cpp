#include "lib/timer/timer_handler.hpp"

namespace gb_lib {

TimerHandler::TimerHandler(InterruptMediator* interruptMediator)
{
    this->interruptMediator = interruptMediator;
    this->divGotReset = false;
    this->div = 0;
    this->tima = 0;
    this->tma = 0;
    this->tac = 0;
}

uint16_t TimerHandler::getDiv()
{
    return this->div;
}

void TimerHandler::setDiv(uint16_t div)
{
    if (this->isSelectedTimerBitUp(this->div, this->getTimerFrequency(this->tac)))
    {
        this->increaseTimer();
    }

    this->divGotReset = true;
    this->div = 0;
}

uint8_t TimerHandler::getTima()
{
    return this->tima;
}

void TimerHandler::setTima(uint8_t tima)
{
    this->tima = tima;
}

uint8_t TimerHandler::getTma()
{
    return this->tma;
}

void TimerHandler::setTma(uint8_t tma)
{
    this->tma = tma;
}

uint8_t TimerHandler::getTac()
{
    return this->tac | 0xF8;
}

void TimerHandler::setTac(uint8_t tac)
{
    if (this->isTimerEnabled(this->tac))
    {
        bool newTimerEnabled = this->isTimerEnabled(tac);
        uint32_t oldFrequency = this->getTimerFrequency(this->tac);

        if (
            (!newTimerEnabled && this->isSelectedTimerBitUp(this->div, oldFrequency)) ||
            (newTimerEnabled && this->didTimerBitChangeFromOneToZero(this->div, this->div, oldFrequency, this->getTimerFrequency(tac)))
        )
        {
            this->increaseTimer();
        }
    }


    this->tac = tac;
}

void TimerHandler::update(uint32_t consumedCpuCycles)
{
    uint32_t cycleIncrease = this->adjustConsumedCpuCycles(consumedCpuCycles);
    uint16_t previousDivValue = this->div;

    this->div += cycleIncrease;

    if (this->isTimerEnabled(this->tac))
    {
        uint32_t timerFrequency = this->getTimerFrequency(this->tac);

        for (uint16_t i = 0; i < cycleIncrease; i++)
        {
            if (this->didTimerBitChangeFromOneToZero(previousDivValue, previousDivValue + 1, timerFrequency, timerFrequency))
            {
                this->increaseTimer();
            }

            previousDivValue++;
        }
    }
}

bool TimerHandler::didTimerBitChangeFromOneToZero(uint16_t divValue1, uint16_t divValue2, uint32_t timerFrequency1, uint32_t timerFrequency2)
{
    // https://gbdev.github.io/pandocs/Timer_Obscure_Behaviour.html#relation-between-timer-and-divider-register
    // if the bit (determined by timer frequency) goes from HIGH to LOW, increase timer
    return (
            this->isSelectedTimerBitUp(divValue1, timerFrequency1) == true &&
            this->isSelectedTimerBitUp(divValue2, timerFrequency2) == false
    );
}

bool TimerHandler::isTimerEnabled(uint8_t tac)
{
    return BitUtil::getBit(tac, 2);
}

bool TimerHandler::isSelectedTimerBitUp(uint16_t divValue, uint32_t timerFrequency)
{
    return (divValue & this->timerIncreaseMask & (timerFrequency >> 1)) != 0;
}

// specific to the way thing are done in this emulator
uint32_t TimerHandler::adjustConsumedCpuCycles(uint32_t consumedCpuCycle)
{
    if (this->divGotReset)
    {
        this->divGotReset = false;
        return 0;
    }

    return consumedCpuCycle;
}

uint32_t TimerHandler::getTimerFrequency(uint8_t tac)
{
    return this->timerFrequencies[tac & 3];
}

void TimerHandler::increaseTimer()
{
    if (this->tima == 0xFF)
  {
      // should be delayed by 4 cpu cycle
      this->tima = this->tma;
      this->interruptMediator->requestInterrupt(Interrupt::TIMER);
  }
  else
  {
      this->tima += 1;
  }
}

}
