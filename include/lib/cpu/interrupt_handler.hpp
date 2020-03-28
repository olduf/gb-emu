#ifndef _CPU_INTERRUPT_HANDLER_H_
#define _CPU_INTERRUPT_HANDLER_H_

#include <cstdint>

#include "lib/cpu/instructions.hpp"
#include "lib/cpu/interrupt.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/memory_space.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class InterruptHandler
{
public:
    InterruptHandler(MemorySpace* mmu, Registers* registers);

    void runEI();
    void handleEI();
    void requestInterrupt(Interrupt interrupt);

    bool isHaltBugState();
    bool isInterruptRequested();

    Instruction* getInterruptInstruction();

private:
    bool needsToEnableInterrupt;
    MemorySpace* mmu;
    Registers* registers;
};

}

#endif
