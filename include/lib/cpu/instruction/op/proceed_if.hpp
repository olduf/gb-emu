#ifndef _CPU_INSTRUCTION_OP_PROCEED_IF_H_
#define _CPU_INSTRUCTION_OP_PROCEED_IF_H_

#include <cstdint>

#include "lib/cpu/instruction/op/flag_condition.hpp"
#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"

namespace gb_lib {

class ProceedIf : public Op
{
public:
    ProceedIf(FlagCondition condition);

    bool canProceed();
    int32_t execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context);

private:
    bool ableToProceed;
    FlagCondition condition;
};

}

#endif
