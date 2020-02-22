#include "lib/cpu/instruction/op/load.hpp"

namespace gb_lib {

Load::Load(const InstructionArgument* source)
{
    this->source = source;
}

uint32_t Load::getArgumentLengthInBytes()
{
    return this->source->getArgumentLengthInBytes();
}

int32_t Load::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    return this->source->get(registers, mmu, opArgument);
}

}
