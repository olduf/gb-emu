#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

bool Op::canProceed()
{
    return true;
}

uint32_t Op::getArgumentLengthInBytes()
{
    return 0;
}

int32_t Op::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    return context;
}

}
