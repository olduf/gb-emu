#include "lib/cpu/instruction/op/alu/compare.hpp"

namespace gb_lib {

Compare::Compare(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t Compare::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t Compare::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int32_t operand = this->argument->get(registers, mmu, opArgument);
    Flags& flags = registers->getFlags();

    flags.setZero(((context - operand) & 0xFF) == 0);
    flags.setSubtraction(true);
    flags.setHalfCarry((operand & 0x0F) > (context & 0x0F));
    flags.setCarry(operand > context);

    return context;
}

}
