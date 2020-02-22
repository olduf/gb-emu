#include "lib/cpu/instruction/op/alu/xor_bytes.hpp"

namespace gb_lib {

XorBytes::XorBytes(const InstructionArgument* argument)
{
    this->argument = argument;
}

uint32_t XorBytes::getArgumentLengthInBytes()
{
    return this->argument->getArgumentLengthInBytes();
}

int32_t XorBytes::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    int32_t operand = this->argument->get(registers, mmu, opArgument);
    int32_t result = (context ^ operand) & 0xFF;

    Flags& flags = registers->getFlags();

    flags.setZero(result == 0);
    flags.setSubtraction(false);
    flags.setHalfCarry(false);
    flags.setCarry(false);

    return result;
}

}
