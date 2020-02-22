#include "lib/cpu/instruction/op/enable_interrupts.hpp"

namespace gb_lib {

EnableInterrupts::EnableInterrupts(bool value)
{
    this->value = value;
}

int32_t EnableInterrupts::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    registers->setIME(this->value);

    return context;
}

}
