#include "lib/graphic/lcd_handler.hpp"

namespace gb_lib {

LCDHandler::LCDHandler(InterruptHandler* interruptHandler, MemorySpace* ioRegisters, PPU* ppu, bool isCGB)
{
    this->cpuCycle = 0;
    this->interruptHandler = interruptHandler;
    this->ioRegisters = ioRegisters;
    this->ppu = ppu;
    this->isCGB = isCGB;
}

void LCDHandler::updateLCD(uint32_t consumedCpuCycle)
{
    // might return LCDC here instead of re-fetching it from mmu
    this->handleLCDStatus();

    uint8_t lcdControl = this->ioRegisters->getByte(LCDC);

    if (!this->isLCDEnabled(lcdControl))
    {
        return;
    }

    this->cpuCycle += consumedCpuCycle;

    if (this->cpuCycle >= this->cyclePerScanLine)
    {
        this->cpuCycle -= this->cyclePerScanLine;

        uint8_t currentScanline = this->ioRegisters->getByte(LY) + 1;

        if (currentScanline < 144)
        {
            this->ppu->drawScanLine(
                this->areBackgroundEnabled(lcdControl),
                this->areOBJEnabled(lcdControl),
                this->areWindowEnabled(lcdControl),
                this->getObjComposition(lcdControl),
                this->getBackgroundTileMapAddress(lcdControl),
                this->getTileDataAddress(lcdControl),
                this->getWindowTileMapAddress(lcdControl),
                currentScanline);
        }
        else if (currentScanline == 144)
        {
            this->interruptHandler->requestInterrupt(Interrupt::VBLANK);
        }
        else if (currentScanline > 153)
        {
            currentScanline = 0;
        }

        this->ioRegisters->setByteInternal(LY, currentScanline);
    }
}

bool LCDHandler::areBackgroundEnabled(uint8_t lcdc)
{
    return this->isCGB || ((lcdc & 1) == 1);
}

bool LCDHandler::areOBJEnabled(uint8_t lcdc)
{
    return BitUtil::getBit(lcdc, 1);
}

bool LCDHandler::areWindowEnabled(uint8_t lcdc)
{
    return BitUtil::getBit(lcdc, 5);
}

bool LCDHandler::isLCDEnabled(uint8_t lcdc)
{
    return BitUtil::getBit(lcdc, 7);
}

ObjComposition LCDHandler::getObjComposition(uint8_t lcdc)
{
    return static_cast<ObjComposition>(lcdc & 4);
}

uint16_t LCDHandler::getBackgroundTileMapAddress(uint8_t lcdc)
{
    if (BitUtil::getBit(lcdc, 3))
    {
        return 0x9C00;
    }

    return 0x9800;
}

uint16_t LCDHandler::getTileDataAddress(uint8_t lcdc)
{
    if (BitUtil::getBit(lcdc, 4))
    {
        return 0x8000;
    }

    return 0x8800;
}

uint16_t LCDHandler::getWindowTileMapAddress(uint8_t lcdc)
{
    if (BitUtil::getBit(lcdc, 6))
    {
        return 0x9C00;
    }

    return 0x9800;
}

// TODO - refactor?
void LCDHandler::handleLCDStatus()
{
    LCDStatusUtil lcdStatusUtil;
    uint8_t lcdControl = this->ioRegisters->getByte(LCDC);
    uint8_t lcdStatus = this->ioRegisters->getByte(STAT);

    // need to reset everything if lcd is disabled
    if (!this->isLCDEnabled(lcdControl))
    {
        this->cpuCycle = 0;
        this->ioRegisters->setByteInternal(LY, 0);
        lcdStatusUtil.setLCDMode(this->ioRegisters, lcdStatus, LCDMode::VBLANK);

        return;
    }

    // Adjust the status to match the phase the rendering cycle
    LCDMode currentMode = lcdStatusUtil.getLCDMode(lcdStatus);
    LCDMode newMode = currentMode;
    bool requiresInterrupt = false;

    uint8_t currentScanline = this->ioRegisters->getByte(LY);

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

    if (currentScanline == this->ioRegisters->getByte(LYC))
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
    lcdStatusUtil.setLCDMode(this->ioRegisters, lcdStatus, newMode);
}

}
