#include "lib/graphic/lcd_handler.hpp"

namespace gb_lib {

LCDHandler::LCDHandler(InterruptHandler* interruptHandler, MemorySpace* mmu, bool isCGB)
{
    this->cpuCycle = 0;
    this->interruptHandler = interruptHandler;
    this->isCGB = isCGB;
    this->mmu = mmu;
}

void LCDHandler::updateLCD(uint32_t consumedCpuCycle)
{
    // might return LCDC here instead of re-fetching it from mmu
    this->handleLCDStatus();

    uint8_t lcdControl = this->mmu->getByte(LCDC);

    if (!this->isLCDEnabled(lcdControl))
    {
        return;
    }

    this->cpuCycle += consumedCpuCycle;

    if (this->cpuCycle >= this->cyclePerScanLine)
    {
        this->cpuCycle -= this->cyclePerScanLine;

        uint8_t currentScanline = this->mmu->getByte(LY) + 1;

        if (currentScanline < 144)
        {
            // draw line
        }
        else if (currentScanline == 144)
        {
            this->interruptHandler->requestInterrupt(Interrupt::VBLANK);
        }
        else if (currentScanline > 153)
        {
            currentScanline = 0;
        }

        this->mmu->setByteInternal(LY, currentScanline);
    }
}

bool LCDHandler::areBackgroundEnabled(uint8_t lcdc)
{
    return this->isCGB || ((lcdc & 1) == 1);
}

bool LCDHandler::areOBJEnabled(uint8_t lcdc)
{
    return (lcdc & 2) != 0;
}

bool LCDHandler::areWindowEnabled(uint8_t lcdc)
{
    return (lcdc & 0x20) != 0;
}

bool LCDHandler::isLCDEnabled(uint8_t lcdc)
{
    return (lcdc & 0x80) != 0;
}

ObjComposition LCDHandler::getObjComposition(uint8_t lcdc)
{
    return static_cast<ObjComposition>(lcdc & 4);
}

LCDMode LCDHandler::getLCDMode(uint8_t stat)
{
    return static_cast<LCDMode>(stat & 3);
}

void LCDHandler::setLCDMode(uint8_t stat, LCDMode lcdMode)
{
    this->mmu->setByteInternal(STAT, (stat & 0xFC) | static_cast<uint8_t>(lcdMode));
}

// TODO - refactor?
void LCDHandler::handleLCDStatus()
{
    uint8_t lcdControl = this->mmu->getByte(LCDC);
    uint8_t lcdStatus = this->mmu->getByte(STAT);

    // need to reset everything if lcd is disabled
    if (!this->isLCDEnabled(lcdControl))
    {
        this->cpuCycle = 0;
        this->mmu->setByteInternal(LY, 0);
        this->setLCDMode(lcdStatus, LCDMode::VBLANK);

        return;
    }

    // Adjust the status to match the phase the rendering cycle
    LCDMode currentMode = this->getLCDMode(lcdStatus);
    LCDMode newMode = currentMode;
    bool requiresInterrupt = false;

    uint8_t currentScanline = this->mmu->getByte(LY);

    if (currentScanline >=  144)
    {
        newMode = LCDMode::VBLANK;
        requiresInterrupt = BitUtil::getBit(lcdStatus, 4);
    }
    else if (this->cpuCycle <= this->oamSearchMaxCycle)
    {
        newMode = LCDMode::OAM_SEARCH;
        requiresInterrupt = BitUtil::getBit(lcdStatus, 5);
    }
    else if (this->cpuCycle <= this->pixelTransferMaxCycle)
    {
        newMode = LCDMode::PIXEL_TRANSFER;
    }
    else
    {
        newMode = LCDMode::HBLANK;
        requiresInterrupt = BitUtil::getBit(lcdStatus, 3);
    }

    // Handle interrupts
    if (newMode != currentMode && requiresInterrupt)
    {
        this->interruptHandler->requestInterrupt(Interrupt::LCD);
    }

    if (currentScanline == this->mmu->getByte(LYC))
    {
        lcdStatus = BitUtil::setBit(lcdStatus, 2);

        // check if we need to trigger the LYC=LY coincidence interrupt
        if (BitUtil::getBit(lcdStatus, 6))
        {
            this->interruptHandler->requestInterrupt(Interrupt::LCD);
        }
    }
    else
    {
        lcdStatus = BitUtil::clearBit(lcdStatus, 2);
    }

    // update status in memory
    this->setLCDMode(lcdStatus, newMode);
}

}