#include "lib/cpu/instruction/op/alu/subtract.hpp"

namespace gb_lib {

Subtract::Subtract(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t Subtract::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t Subtract::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int32_t operand = this->argument->get(registers, mmu, opArgument);

    int32_t result = context - operand;

    Flags& flags = registers->getFlags();
    flags.setZero((result & 0xFF) == 0);
    flags.setSubtraction(true);
    flags.setHalfCarry((operand & 0x0F) > (context & 0x0F));
    flags.setCarry(operand > context);

    return result;
}

}
