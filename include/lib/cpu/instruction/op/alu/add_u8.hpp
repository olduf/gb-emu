#ifndef _CPU_INSTRUCTION_OP_ALU_ADD_U8_H_
#define _CPU_INSTRUCTION_OP_ALU_ADD_U8_H_

#include "lib/cpu/instruction/op/affect_flags_type.hpp"
#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/instruction/instruction_argument.hpp"

namespace gb_lib {

class AddU8 : public Op
{
public:
    AddU8(const InstructionArgument* argument);

    uint32_t getArgumentLengthInBytes();
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    const InstructionArgument* argument;
};

}

#endif
