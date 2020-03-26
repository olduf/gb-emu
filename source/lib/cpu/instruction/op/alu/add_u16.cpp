#include "lib/cpu/instruction/op/alu/add_u16.hpp"

namespace gb_lib {

AddU16::AddU16(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t AddU16::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t AddU16::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int32_t operand = this->argument->get(registers, mmu, opArgument);
    int32_t result = context + operand;

    Flags& flags = registers->getFlags();
    flags.setSubtraction(false);
    flags.setHalfCarry((context & 0x0FFF) + (operand & 0x0FFF) > 0x0FFF);
    flags.setCarry(result > 0xFFFF);

    return result & 0xFFFF;
}

}
