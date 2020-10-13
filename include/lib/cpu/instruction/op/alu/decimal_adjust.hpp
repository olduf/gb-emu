#pragma once

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class DecimalAdjust : public Op
{
public:
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);
};

}
