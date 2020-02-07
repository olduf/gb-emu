#ifndef _CPU_H_
#define _CPU_H_

#include <cstdint>

#include "lib/cpu/instructions.hpp"
#include "lib/cpu/interrupt_handler.hpp"
#include "lib/cpu/registers.hpp"
#include "lib/cpu/speedmode_handler.hpp"
#include "lib/cpu/state.hpp"
#include "lib/memory/mmu.hpp"

namespace gb_lib {

const uint8_t CB_PREFIX = 0xCB;
const uint8_t EI = 0xFB;
const uint8_t HALT = 0x76;
const uint8_t STOP = 0x10;

class Cpu
{
public:
    Cpu(InterruptHandler* interruptHandler, MMU* mmu, Registers* registers, SpeedModeHandler* speedModeHandler);

    uint32_t tick();

private:
    CpuState cpuState;
    InterruptHandler* interruptHandler;
    MMU* mmu;
    Registers* registers;
    SpeedModeHandler* speedModeHandler;
};

}

#endif
