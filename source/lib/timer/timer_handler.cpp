#include "lib/timer/timer_handler.hpp"
#include <cstdio>

namespace gb_lib {

TimerHandler::TimerHandler(InterruptMediator* interruptMediator, SetTacAuditor* setTacAuditor, TimerUtil* timerUtil)
{
    this->interruptMediator = interruptMediator;
    this->setTacAuditor = setTacAuditor;
    this->timerUtil = timerUtil;

    this->divJustReset = false;
    this->tacJustSet = false;
    this->timaCircuitUp = false;
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
    if (this->timerUtil->isTimaCircuitUp(div, this->tac))
    {
        this->increaseTimer();
    }

    this->timaCircuitUp = false;
    this->divJustReset = true;
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
    if (this->setTacAuditor->needToIncreaseTima(this->div, this->tac, tac))
    {
        this->increaseTimer();
    }

    this->tacJustSet = true;
    this->tac = tac;
}

void TimerHandler::update(uint32_t consumedCpuCycles)
{
    uint32_t cycleIncrease = this->adjustConsumedCpuCycles(consumedCpuCycles);
    uint16_t previousDivValue = this->div;

    this->div += cycleIncrease;

    if (this->timerUtil->isTimerEnabled(this->tac) && !this->tacJustSet)
    {
        for (uint16_t i = 0; i < cycleIncrease; i++)
        {
            bool newTimaCircuitUp = this->timerUtil->isTimaCircuitUp(previousDivValue + 1, this->tac);

            if (this->timaCircuitUp && !newTimaCircuitUp)
            {
                this->increaseTimer();
            }

            this->timaCircuitUp = newTimaCircuitUp;
            previousDivValue++;
        }
    }

    this->tacJustSet = false;
    this->timaCircuitUp = this->timerUtil->isTimaCircuitUp(this->div, this->tac);
}

// specific to the way thing are done in this emulator
uint32_t TimerHandler::adjustConsumedCpuCycles(uint32_t consumedCpuCycle)
{
    if (this->divJustReset)
    {
        this->divJustReset = false;
        return 0;
    }

    return consumedCpuCycle;
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
