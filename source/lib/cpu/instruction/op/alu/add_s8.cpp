#include "lib/cpu/instruction/op/alu/add.hpp"

namespace gb_lib {

Add::Add(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t Add::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t Add::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    int32_t operand = this->argument->get(registers, mmu, opArgument);
    int32_t result = context + operand;

    return result;
}

}
