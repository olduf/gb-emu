#ifndef _CPU_INSTRUCTION_OP_STORE_H_
#define _CPU_INSTRUCTION_OP_STORE_H_

#include <cstdint>

#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/instruction/instruction_argument.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"

namespace gb_lib {

class Store : public Op
{
public:
    Store(const InstructionArgument* destination);

    uint32_t getArgumentLengthInBytes();
    int32_t execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context);

private:
    const InstructionArgument* destination;
};

}

#endif
