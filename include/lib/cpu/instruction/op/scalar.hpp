#pragma once

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class Scalar : public Op
{
public:
    Scalar(uint32_t value);

    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    uint32_t value;
};

}
