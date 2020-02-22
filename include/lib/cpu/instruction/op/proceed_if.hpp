#ifndef _CPU_INSTRUCTION_OP_PROCEED_IF_H_
#define _CPU_INSTRUCTION_OP_PROCEED_IF_H_

#include "lib/cpu/instruction/op/flag_condition.hpp"
#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class ProceedIf : public Op
{
public:
    ProceedIf(FlagCondition condition);

    bool canProceed();
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    bool ableToProceed;
    FlagCondition condition;
};

}

#endif
