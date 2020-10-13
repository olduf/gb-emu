#pragma once

#include "lib/cpu/instruction/op/affect_flags_type.hpp"
#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/instruction/instruction_argument.hpp"

namespace gb_lib {

class AddS8 : public Op
{
public:
    AddS8(const InstructionArgument* argument);

    uint32_t getArgumentLengthInBytes();
    virtual int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    const InstructionArgument* argument;
};

}
