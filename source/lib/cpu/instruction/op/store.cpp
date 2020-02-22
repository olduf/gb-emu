#include "lib/cpu/instruction/op/store.hpp"

namespace gb_lib {

Store::Store(const InstructionArgument* destination)
{
    this->destination = destination;
}

uint32_t Store::getArgumentLengthInBytes()
{
    return this->destination->getArgumentLengthInBytes();
}

int32_t Store::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    this->destination->set(registers, mmu, opArgument, context);

    return context;
}

}
