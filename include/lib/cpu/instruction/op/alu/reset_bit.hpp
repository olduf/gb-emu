#ifndef _CPU_INSTRUCTION_OP_ALU_RESET_BIT_H_
#define _CPU_INSTRUCTION_OP_ALU_RESET_BIT_H_

#include <cstdint>

#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class ResetBit : public Op
{
public:
    ResetBit(uint8_t n);

    int32_t execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context);

private:
    uint8_t n;
};

}

#endif
