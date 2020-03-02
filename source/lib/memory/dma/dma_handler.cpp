#include "lib/memory/dma/dma_handler.hpp"

namespace gb_lib {

DMAHandler::DMAHandler(MemorySpace* mmu, DMAMediator* dmaMediator, SpeedModeHandler* speedModeHandler)
{
    this->mmu = mmu;
    this->dmaMediator = dmaMediator;
    this->speedModeHandler = speedModeHandler;
}

void DMAHandler::tick(uint32_t consumedCpuCycle)
{
    this->setUpTransfer();

    if (this->dmaMediator->isTransferInProgress())
    {
        this->cpuCycle += consumedCpuCycle;

        if (this->cpuCycle >= this->cyclesNeededToComplete / static_cast<uint32_t>(this->speedModeHandler->getSpeedMode()))
        {
            this->dmaMediator->setTransferInProgress(false);

            for (uint16_t i = 0; i < 160; ++i)
            {
                this->mmu->setByte(OAM_START + i, this->mmu->getByte(this->source + i));
            }
        }
    }
}

void DMAHandler::setUpTransfer()
{
    if (!this->dmaMediator->isTransferInProgress() && this->dmaMediator->isTransferRequested())
    {
        this->dmaMediator->requestTransfer(false);
        uint16_t source = this->mmu->getByte(DMA);

        // GameBoy Programming Manual v1.1 - page 22
        // DMA transfers from 0x8000 - 0xDFFF. Must be in increment of 0x100.
        if (source >= 0x8000 && source <= 0xDF00 && (source & 0x00FF) == 0)
        {
            this->dmaMediator->setTransferInProgress(true);
            this->source = source;
            this->cpuCycle = 0;
        }
    }
}

}
