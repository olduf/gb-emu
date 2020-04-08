#include "lib/cpu/interrupt_handler.hpp"

namespace gb_lib {

InterruptHandler::InterruptHandler(InterruptMediator* interruptMediator, MemorySpace* mmu, Registers* registers)
{
   this->needsToEnableInterrupt = false;
   this->interruptMediator = interruptMediator;
   this->mmu = mmu;
   this->registers = registers;
}

void InterruptHandler::runEI()
{
    this->needsToEnableInterrupt = true;
}

void InterruptHandler::handleEI()
{
    if (this->needsToEnableInterrupt == true)
    {
        this->needsToEnableInterrupt = false;
        this->registers->setIME(true);
  }
}

void InterruptHandler::requestInterrupt(Interrupt interrupt)
{
    this->interruptMediator->requestInterrupt(interrupt);
}

bool InterruptHandler::isHaltBugState()
{
    return !this->registers->isIME() && this->isInterruptRequested();
}

bool InterruptHandler::isInterruptRequested()
{
    return (this->interruptMediator->getIF() & this->mmu->getByte(IE) & 0x1F) != 0;
}

Instruction* InterruptHandler::getInterruptInstruction()
{
    if (this->registers->isIME())
    {
        uint8_t interruptFlag = this->interruptMediator->getIF();
        uint8_t interruptEnabled = this->mmu->getByte(IE);
        uint8_t interruptToRun = interruptFlag & interruptEnabled;

        for (uint8_t i = 0; i < 5; i++)
        {
            if (BitUtil::getBit(interruptToRun, i))
            {
                this->interruptMediator->setIF(BitUtil::clearBit(interruptFlag, i));
                this->registers->setIME(false);

                return interrupts[i];
            }
        }
    }

    return nullptr;
}

}
