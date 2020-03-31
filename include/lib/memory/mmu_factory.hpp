#ifndef _MEMORY_FACTORY_H_
#define _MEMORY_FACTORY_H_

#include "lib/memory/cartridge/cartridge_factory.hpp"
#include "lib/memory/cgb_unused_memory_fea0_feff.hpp"
#include "lib/memory/cgb_vram.hpp"
#include "lib/memory/cgb_working_ram.hpp"
#include "lib/memory/high_ram.hpp"
#include "lib/memory/io_registers.hpp"
#include "lib/memory/mmu.hpp"
#include "lib/memory/oam.hpp"
#include "lib/memory/unused_memory_fea0_feff.hpp"
#include "lib/memory/vram.hpp"
#include "lib/memory/working_ram.hpp"
#include "lib/timer/timer_mediator.hpp"

namespace gb_lib {

class MMUFactory
{
public:
    MMU* create(uint8_t* rom, uint32_t romSize, DMAMediator* dmaMediator, DMAMediator* hdmaMediator, TimerMediator* timerMediator, bool isCGB);

private:
    MemorySpace* createHighRam(bool isCGB);
    MemorySpace* createIORegisters(DMAMediator* dmaMediator, DMAMediator* hdmaMediator, TimerMediator* timerMediator, bool isCGB);

private:
    CartridgeFactory cartridgeFactory;
};

}

#endif
