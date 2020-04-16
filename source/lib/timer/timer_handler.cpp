#include "lib/timer/timer_handler.hpp"

/*
 *  In this emulator, cpu instructions are executed as a single block.
 *  Each components is then updated by the consumed cpu cycles.
 *
 *  In real hardware, the timer would be increased in parallel, which means we
 *  need to be a little hacky to make the timer behave as it should.
 */

namespace gb_lib {

TimerHandler::TimerHandler(InterruptMediator* interruptMediator, SetTacAuditor* setTacAuditor, TimerUtil* timerUtil)
{
    this->interruptMediator = interruptMediator;
    this->setTacAuditor = setTacAuditor;
    this->timerUtil = timerUtil;

    this->valueJustSet = false;

    this->timaCircuitUp = false;
    this->timerWasHandledInternally = false;

    this->div = 0;
    this->tima = 0;
    this->tma = 0;
    this->tac = 0;
}

uint16_t TimerHandler::getDiv()
{
    this->handleTimerInternally();

    return this->div;
}

void TimerHandler::setDiv(uint16_t div)
{
    this->handleTimerInternally();

    if (this->timerUtil->isTimaCircuitUp(this->div, this->tac))
    {
        this->increaseTimer();
    }

    this->timaCircuitUp = false;

    this->div = 0;
}

uint8_t TimerHandler::getTima(bool debug)
{
    if (debug) { return this->tima; }

    this->handleTimerInternally();

    return this->tima;
}

void TimerHandler::setTima(uint8_t tima)
{
    this->valueJustSet = true;

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

    this->valueJustSet = true;
    this->tac = tac;
}

void TimerHandler::update(uint32_t consumedCpuCycles)
{
    uint32_t cycleIncrease = this->adjustConsumedCpuCycles(consumedCpuCycles);
    uint16_t previousDivValue = this->div;

    this->div += cycleIncrease;

    if (this->timerUtil->isTimerEnabled(this->tac) && !this->valueJustSet)
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

    this->valueJustSet = false;
    this->timaCircuitUp = this->timerUtil->isTimaCircuitUp(this->div, this->tac);
}

// specific to the way thing are done in this emulator
uint32_t TimerHandler::adjustConsumedCpuCycles(uint32_t consumedCpuCycle)
{
    if (this->timerWasHandledInternally)
    {
        this->timerWasHandledInternally = false;

        return 0;
    }

    return consumedCpuCycle;
}

void TimerHandler::handleTimerInternally()
{
    this->update(this->instruction_duration);

    this->timerWasHandledInternally = true;
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
