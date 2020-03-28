#include "lib/cpu/interrupt_handler.hpp"

namespace gb_lib {

InterruptHandler::InterruptHandler(MemorySpace* mmu, Registers* registers)
{
   this->needsToEnableInterrupt = false;
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
    uint8_t updatedInterruptFlagValue = BitUtil::setBit(this->mmu->getByte(IF), static_cast<uint8_t>(interrupt));

    this->mmu->setByte(IF, updatedInterruptFlagValue);
}

bool InterruptHandler::isHaltBugState()
{
    return !this->registers->isIME() && this->isInterruptRequested();
}

bool InterruptHandler::isInterruptRequested()
{
    return (this->mmu->getByte(IF) & this->mmu->getByte(IE) & 0x1F) != 0;
}

Instruction* InterruptHandler::getInterruptInstruction()
{
    if (this->registers->isIME())
    {
        uint8_t interruptFlag = this->mmu->getByte(IF);
        uint8_t interruptEnabled = this->mmu->getByte(IE);
        uint8_t interruptToRun = interruptFlag & interruptEnabled;

        for (uint8_t i = 0; i < 5; i++)
        {
            if (BitUtil::getBit(interruptToRun, i))
            {
                this->mmu->setByte(IF, BitUtil::clearBit(interruptFlag, i));
                this->registers->setIME(false);

                return interrupts[i];
            }
        }
    }

    return nullptr;
}

}
