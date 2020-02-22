#ifndef _CPU_INSTRUCTION_OP_ALU_DECREMENT_H_
#define _CPU_INSTRUCTION_OP_ALU_DECREMENT_H_

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class Decrement : public Op
{
public:
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);
};

}

#endif
