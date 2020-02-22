#include "lib/cpu/instruction/op/alu/add_u8.hpp"

namespace gb_lib {

AddU8::AddU8(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t AddU8::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t AddU8::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int32_t operand = this->argument->get(registers, mmu, opArgument);
    int32_t result = context + operand;

    Flags& flags = registers->getFlags();
    flags.setSubtraction(false);
    flags.setZero((result & 0xFF) == 0);
    flags.setHalfCarry((context & 0x0F) + (operand & 0x0F) > 0x0F);
    flags.setCarry(result > 0xFF);

    return result;
}

}
