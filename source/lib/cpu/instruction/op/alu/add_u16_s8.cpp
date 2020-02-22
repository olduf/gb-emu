#include "lib/cpu/instruction/op/alu/add_u16_s8.hpp"

namespace gb_lib {

AddU16S8::AddU16S8(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t AddU16S8::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t AddU16S8::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int8_t operand = (int8_t)this->argument->get(registers, mmu, opArgument);
    int32_t result = context + operand;

    Flags& flags = registers->getFlags();
    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry((context & 0x0F) + (operand & 0x0F) > 0x0F);
    flags.setCarry(result > 0xFFFF);

    return result;
}

}
