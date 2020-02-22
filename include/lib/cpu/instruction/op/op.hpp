#ifndef _CPU_INSTRUCTION_OP_OP_H_
#define _CPU_INSTRUCTION_OP_OP_H_

#include "lib/cpu/registers.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class Op
{
public:
    virtual ~Op() = default;

    virtual bool canProceed();
    virtual uint32_t getArgumentLengthInBytes();
    virtual int32_t execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context);
};

}

#endif
