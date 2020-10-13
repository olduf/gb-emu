#pragma once

#include "lib/cpu/speedmode_handler.hpp"
#include "lib/graphic/lcd_status_util.hpp"
#include "lib/memory/dma/dma_mediator.hpp"
#include "lib/memory/dma/hdma_transfer_type.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class HDMAHandler
{
public:
    HDMAHandler(MemorySpace* mmu, DMAMediator* hdmaMediator, SpeedModeHandler* speedModeHandler);

    void tick(uint32_t consumedCpuCycle);

    bool isTransferInProgress();

private:
    void setUpTransfer();
    void setInitialTransferState();

private:
    bool transferInProgress;
    DMAMediator* hdmaMediator;
    HDMATransferType transferType;
    MemorySpace* mmu;
    SpeedModeHandler* speedModeHandler;
    uint8_t transferedBytesInHBLANK;
    uint16_t source;
    uint16_t destination;
    uint32_t cpuCycle;
    uint32_t neededCpuCycle;
    uint32_t numberOfBytesToTransfer;
};

}
