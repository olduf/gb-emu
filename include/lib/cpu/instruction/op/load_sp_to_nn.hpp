#ifndef _CPU_INSTRUCTION_OP_LOAD_SP_TO_NN_H_
#define _CPU_INSTRUCTION_OP_LOAD_SP_TO_NN_H_

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class LoadSPToNN : public Op
{
public:
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);
};

}

#endif
