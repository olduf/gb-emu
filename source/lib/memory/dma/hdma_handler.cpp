#include "lib/memory/dma/hdma_handler.hpp"

namespace gb_lib {

// TODO - refactor this atrocity
HDMAHandler::HDMAHandler(MemorySpace* mmu, DMAMediator* hdmaMediator, SpeedModeHandler* speedModeHandler)
{
    this->transferInProgress = false;
    this->mmu = mmu;
    this->hdmaMediator = hdmaMediator;
    this->speedModeHandler = speedModeHandler;
    this->transferType = HDMATransferType::GENERAL;
}

void HDMAHandler::tick(uint32_t consumedCpuCycle)
{
    this->setUpTransfer();

    if (this->isTransferInProgress())
    {
        if (this->transferType == HDMATransferType::GENERAL)
        {
            this->cpuCycle += consumedCpuCycle;

            if (this->cpuCycle >= this->neededCpuCycle)
            {
                this->hdmaMediator->setTransferInProgress(false);

                for (uint16_t i = 0; i < this->numberOfBytesToTransfer; i++)
                {
                    this->mmu->setByte(this->destination + i, this->mmu->getByte(this->source + i));
                }
            }
        }
        else
        {
            this->mmu->setByte(this->destination, this->mmu->getByte(this->source));

            this->transferedBytesInHBLANK++;
            this->numberOfBytesToTransfer--;

            this->source++;
            this->destination++;

            // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
            // 9.6.2 - Reading from the HDMA5 register will return the remaining
            // length (divided by 16, minus 1). A value of FFh indicates that the transfer has completed.
            if (this->numberOfBytesToTransfer == 0)
            {
                this->mmu->setByteInternal(HDMA5, 0xFF);
                this->hdmaMediator->setTransferInProgress(false);
            }
            else
            {
                this->mmu->setByteInternal(HDMA5, 0b10000000 | (static_cast<uint8_t>(this->numberOfBytesToTransfer >> 4) - 1));
            }
        }
    }
}

bool HDMAHandler::isTransferInProgress()
{
    if (this->transferType == HDMATransferType::HBLANK && this->hdmaMediator->isTransferInProgress())
    {
        LCDStatusUtil lcdStatusUtil;
        LCDMode currentMode = lcdStatusUtil.getLCDMode(this->mmu->getByteInternal(STAT));

        // TODO - HBLANK DMA does not happen when cpu is in HALT or STOP mode
        if (currentMode == LCDMode::HBLANK)
        {
            return this->numberOfBytesToTransfer > 0 && this->transferedBytesInHBLANK < 16;
        }

        this->transferedBytesInHBLANK = 0;

        return false;
    }

    return this->hdmaMediator->isTransferInProgress();
}

void HDMAHandler::setUpTransfer()
{
    if (!this->hdmaMediator->isTransferInProgress())
    {
        if (this->hdmaMediator->isTransferRequested())
        {
            this->setInitialTransferState();
        }
    }
    // HBLANK DMA can be restarted or canceled by writing to FF55 again.
    // Canceled if bit 7 if zero, restated if bit 7 is one.
    else if (this->transferType == HDMATransferType::HBLANK && this->hdmaMediator->isTransferRequested())
    {
        uint8_t hdma5 = this->mmu->getByteInternal(HDMA5);

        if (static_cast<HDMATransferType>(hdma5 & 0b10000000) == HDMATransferType::GENERAL)
        {
            this->hdmaMediator->requestTransfer(false);
            this->hdmaMediator->setTransferInProgress(false);
            // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
            // 9.6.2 - New bit 7 is 0: Stop copy. HDMA5 new value is (80h OR written_value)
            this->mmu->setByteInternal(HDMA5, hdma5 | 0b10000000);
        }
        else
        {
            this->setInitialTransferState();
        }
    }
}

void HDMAHandler::setInitialTransferState()
{
    this->hdmaMediator->requestTransfer(false);
    this->source = (this->mmu->getByteInternal(HDMA1) << 8) | (this->mmu->getByteInternal(HDMA2) & 0b11110000);

    // source needs to be in rom or external ram
    if (this->source < 0x8000 || (this->source >= 0xA000 && this->source < 0xE000))
    {
        // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
        // 9.4, 9.5 - Destination is always VRAM (0x8000 - 0x9FFF). Upper 3 bits and lower 4 bits are ignored.
        this->destination = ( ((this->mmu->getByteInternal(HDMA3) & 0b00011111) << 8) | (this->mmu->getByteInternal(HDMA4) & 0b11110000) ) | 0x8000;

        uint8_t hdma5 = this->mmu->getByteInternal(HDMA5);
        this->transferType = static_cast<HDMATransferType>(hdma5 & 0x80);
        this->numberOfBytesToTransfer = ((hdma5 & 0b01111111) + 1) * 16;

        // transfer always takes the same time, speed mode does not matter.
        this->neededCpuCycle = 4 + (this->numberOfBytesToTransfer * 2 * static_cast<uint32_t>(this->speedModeHandler->getSpeedMode()));
        this->transferedBytesInHBLANK = 0;
        this->cpuCycle = 0;

        this->hdmaMediator->setTransferInProgress(true);
    }
}

}
