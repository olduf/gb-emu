#ifndef _CPU_INSTRUCTION_OP_SET_FLAG_ZERO_H_
#define _CPU_INSTRUCTION_OP_SET_FLAG_ZERO_H_

#include <cstdint>

#include "lib/cpu/flags.hpp"
#include "lib/cpu/instruction/op/flag_condition.hpp"
#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"

namespace gb_lib {

class SetFlagZero : public Op
{
public:
    SetFlagZero(bool value);

    int32_t execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context);

private:
    bool value;
};

}

#endif
