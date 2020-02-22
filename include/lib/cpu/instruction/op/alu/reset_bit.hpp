#ifndef _CPU_INSTRUCTION_OP_ALU_RESET_BIT_H_
#define _CPU_INSTRUCTION_OP_ALU_RESET_BIT_H_

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class ResetBit : public Op
{
public:
    ResetBit(uint8_t n);

    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    uint8_t n;
};

}

#endif
