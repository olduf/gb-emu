#ifndef _CPU_INSTRUCTION_OP_ALU_SET_BIT_H_
#define _CPU_INSTRUCTION_OP_ALU_SET_BIT_H_

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class SetBit : public Op
{
public:
    SetBit(uint8_t n);

    int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);

private:
    uint8_t n;
};

}

#endif
