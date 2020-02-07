#ifndef _CPU_INSTRUCTION_OP_ALU_TEST_BIT_H_
#define _CPU_INSTRUCTION_OP_ALU_TEST_BIT_H_

#include <cstdint>

#include "lib/cpu/flags.hpp"
#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"

namespace gb_lib {

class TestBit : public Op
{
public:
    TestBit(uint8_t n);

    int32_t execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context);

private:
    uint8_t n;
};

}

#endif
