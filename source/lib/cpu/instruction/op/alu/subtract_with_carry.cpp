#include "lib/cpu/instruction/op/alu/subtract_with_carry.hpp"

namespace gb_lib {

SubtractWithCarry::SubtractWithCarry(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t SubtractWithCarry::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t SubtractWithCarry::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();

    int32_t carry = flags.isCarry() ? 1 : 0;
    int32_t operand = this->argument->get(registers, mmu, opArgument);
    int32_t result = context - operand - carry;

    flags.setZero((result & 0xFF) == 0);
    flags.setSubtraction(true);
    flags.setHalfCarry(((context ^ operand ^ (result & 0xFF)) & 0x10) != 0);
    flags.setCarry(operand + carry > (context & 0xFF));

    return result;
}

}
