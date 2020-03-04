#include "lib/graphic/ppu.hpp"

namespace gb_lib {

PPU::PPU(MemorySpace* mmu, Renderer* renderer)
{
    this->mmu = mmu;
    this->renderer = renderer;
}

void PPU::drawScanLine(
    bool backgroundEnabled,
    bool objectEnabled,
    bool windowEnabled,
    ObjComposition objectComposition,
    uint16_t bgTileMapAddress,
    uint16_t tileDataAddress,
    uint16_t windowTileMapAddress,
    uint8_t scanLine)
{
    uint8_t scrollY = this->mmu->getByte(SCY);
    uint8_t scrollX = this->mmu->getByte(SCX);
    uint8_t windowY = this->mmu->getByte(WY);
    uint8_t windowX = this->mmu->getByte(WX) - 7;

    uint16_t tileMapAddress = 0;
    uint8_t yPosition = 0;
    bool usingWindow = false;

    if (windowEnabled && windowY <= scanLine)
    {
        tileMapAddress = windowTileMapAddress;
        yPosition = scanLine - windowY;
        usingWindow = true;
    }
    else if (backgroundEnabled)
    {
        tileMapAddress = bgTileMapAddress;
        yPosition = scrollY + scanLine;
    }

    if (tileMapAddress != 0)
    {
        this->drawTiles(tileMapAddress, tileDataAddress, scanLine, yPosition, usingWindow);
    }

    if (objectEnabled)
    {
        this->drawObjects(objectComposition, scanLine);
    }
}

void PPU::drawTiles(uint16_t tileMapAddress, uint16_t tileDataAddress, uint8_t scanLine, uint8_t yPos, bool usingWindow)
{
    //
}

void PPU::drawObjects(ObjComposition objectComposition, uint8_t scanLine)
{
    //
}

}
