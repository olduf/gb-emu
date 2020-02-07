#include "lib/cpu/instruction/op/alu/add_with_carry.hpp"

namespace gb_lib {

AddWithCarry::AddWithCarry(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t AddWithCarry::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t AddWithCarry::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    Flags& flags = registers->getFlags();

    int32_t carry = flags.isCarry() ? 1 : 0;
    int32_t operand = this->argument->get(registers, mmu, opArgument);
    int32_t result = context + operand + carry;

    flags.setZero((result & 0xFF) == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry((context & 0x0F) + (operand & 0x0F) + carry > 0x0F);
    flags.setCarry(result > 0xFF);

    return result;
}

}
