#ifndef _CPU_INSTRUCTION_OP_ALU_SET_CARRY_FLAG_H_
#define _CPU_INSTRUCTION_OP_ALU_SET_CARRY_FLAG_H_

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class SetCarryFlag : public Op
{
public:
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);
};

}

#endif
