#ifndef _CPU_INSTRUCTION_OP_ALU_SUBTRACT_H_
#define _CPU_INSTRUCTION_OP_ALU_SUBTRACT_H_

#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/instruction/instruction_argument.hpp"

namespace gb_lib {

class Subtract : public Op
{
public:
    Subtract(const InstructionArgument* argument);

    uint32_t getArgumentLengthInBytes();
    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    const InstructionArgument* argument;
};

}

#endif
