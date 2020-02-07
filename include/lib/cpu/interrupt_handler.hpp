#ifndef _CPU_INTERRUPT_HANDLER_H_
#define _CPU_INTERRUPT_HANDLER_H_

#include <cstdint>

#include "lib/cpu/instructions.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/memory/mmu.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

enum class Interrupt : uint8_t
{
    VBLANK = 0,
    LCD = 1,
    TIMER = 2,
    SERIAL = 3,
    INPUT = 4
};

class InterruptHandler
{
public:
    InterruptHandler(MMU* mmu, Registers* registers);

    void runEI();
    void handleEI();
    void requestInterrupt(Interrupt interrupt);

    Instruction* getInterruptInstruction();

private:
    bool needsToEnableInterrupt;
    MMU* mmu;
    Registers* registers;
};

}

#endif
