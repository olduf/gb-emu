#ifndef _CPU_INSTRUCTION_OP_ENABLE_INTERRUPTS_H_
#define _CPU_INSTRUCTION_OP_ENABLE_INTERRUPTS_H_

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class EnableInterrupts : public Op
{
public:
    EnableInterrupts(bool value);

    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    bool value;
};

}

#endif
