#ifndef _CPU_INSTRUCTION_OP_SET_FLAG_ZERO_H_
#define _CPU_INSTRUCTION_OP_SET_FLAG_ZERO_H_

#include "lib/cpu/instruction/op/flag_condition.hpp"
#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class SetFlagZero : public Op
{
public:
    SetFlagZero(bool value);

    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    bool value;
};

}

#endif
