#ifndef _CPU_INSTRUCTION_OP_JUMP__
#define _CPU_INSTRUCTION_OP_JUMP__

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class Jump : public Op
{
public:
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);
};

}

#endif
