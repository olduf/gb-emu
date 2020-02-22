#include "lib/cpu/instruction/op/alu/add_s8.hpp"

namespace gb_lib {

AddS8::AddS8(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t AddS8::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t AddS8::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int8_t operand = (int8_t)this->argument->get(registers, mmu, opArgument);
    int32_t result = context + operand;

    return result;
}

}
