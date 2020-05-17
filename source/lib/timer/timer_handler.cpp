#include "lib/timer/timer_handler.hpp"

/*
 * In this emulator, cpu instructions are executed as a single block.
 * Each components is then updated by the consumed cpu cycles.
 *
 * In real hardware, the timer would be increased in parallel, which means we
 * need to be a little hacky to make the timer behave as it should.
 *
 * Getting or setting any value in here happens through instructions 0xE0 and 0xF0 (12 cpu cycles each).
 * When these happens, the timer is updated internally so that the right values are returned.
 * A flag is set that the timer does not get updated a second time by the main loop.
 */
namespace gb_lib {

TimerHandler::TimerHandler(InterruptMediator* interruptMediator, SetTacAuditor* setTacAuditor, TimerUtil* timerUtil)
{
    this->interruptMediator = interruptMediator;
    this->setTacAuditor = setTacAuditor;
    this->timerUtil = timerUtil;

    this->timaCircuitUp = false;
    this->timerWasHandledInternally = false;

    this->div = 0;
    this->tima = 0;
    this->tma = 0;
    this->tac = 0;
}

uint8_t TimerHandler::getByte(uint16_t address)
{
    this->handleTimerInternally();

    switch (address)
    {
        case DIV - 1:
            return this->div & 0x00FF;
        case DIV:
            return this->div >> 8;
        case TIMA:
            return this->tima;
        case TMA:
            return this->tma;
        case TAC:
            return this->tac | 0b11111000;
        default:
            return 0;
  }
}

uint8_t TimerHandler::getByteInternal(uint16_t address)
{
    switch (address)
    {
        case DIV - 1:
            return this->div & 0x00FF;
        case DIV:
            return this->div >> 8;
        case TIMA:
            return this->tima;
        case TMA:
            return this->tma;
        case TAC:
            return this->tac;
        default:
            return 0;
    }
}

void TimerHandler::setByte(uint16_t address, uint8_t value)
{
    this->handleTimerInternally();

    switch (address)
    {
        case DIV:
            {
                if (this->timerUtil->isTimaCircuitUp(this->div, this->tac))
                {
                    this->increaseTimer();
                }

                this->timaCircuitUp = false;
                this->div = 0;
            }
            break;
        case TIMA:
            this->tima = value;
            break;
        case TMA:
            this->tma = value;
            break;
        case TAC:
            {
                if (this->setTacAuditor->needToIncreaseTima(this->div, this->tac, value))
                {
                    this->increaseTimer();
                }

                this->tac = value;
            }
            break;
    }
}

void TimerHandler::setByteInternal(uint16_t address, uint8_t value)
{
    switch (address)
    {
        case DIV - 1:
            this->div = (this->div & 0xFF00) | value;
            break;
        case DIV:
            this->div = (this->div & 0x00FF) | (value << 8);
            break;
        case TIMA:
            this->tima = value;
            break;
        case TMA:
            this->tma = value;
            break;
        case TAC:
            this->tac = value;
            break;
    }
}

void TimerHandler::update(uint32_t consumedCpuCycles)
{
    uint32_t cycleIncrease = this->adjustConsumedCpuCycles(consumedCpuCycles);
    uint16_t previousDivValue = this->div;

    this->div += cycleIncrease;

    if (this->timerUtil->isTimerEnabled(this->tac))
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
        // TODO - implement tima reloading behavior
        // https://gbdev.github.io/pandocs/Timer_Obscure_Behaviour.html#timer-overflow-behaviour
        this->tima = this->tma;
        this->interruptMediator->requestInterrupt(Interrupt::TIMER);
    }
    else
    {
        this->tima += 1;
    }
}

}
