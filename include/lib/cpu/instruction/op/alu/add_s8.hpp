#ifndef _CPU_INSTRUCTION_OP_ALU_ADD_S8_H_
#define _CPU_INSTRUCTION_OP_ALU_ADD_S8_H_

#include <cstdint>

#include "lib/cpu/flags.hpp"
#include "lib/cpu/instruction/op/affect_flags_type.hpp"
#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/instruction/instruction_argument.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"

namespace gb_lib {

class AddS8 : public Op
{
public:
    AddS8(const InstructionArgument* argument);

    uint32_t getArgumentLengthInBytes();
    virtual int32_t execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context);

private:
    const InstructionArgument* argument;
};

}

#endif
