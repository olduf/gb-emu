#pragma once

#include "lib/cpu/speedmode_handler.hpp"
#include "lib/memory/dma/dma_mediator.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class DMAHandler
{
public:
    DMAHandler(MemorySpace* mmu, DMAMediator* dmaMediator, SpeedModeHandler* speedModeHandler);

    void tick(uint32_t consumedCpuCycle);
    void setUpTransfer();

private:
    MemorySpace* mmu;
    DMAMediator* dmaMediator;
    SpeedModeHandler* speedModeHandler;
    uint16_t source;
    uint32_t cpuCycle;

private:
    const uint32_t cyclesNeededToComplete = 644;
};

}
