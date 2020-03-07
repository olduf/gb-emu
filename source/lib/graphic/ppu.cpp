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
    uint8_t windowY = this->mmu->getByte(WY);

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

void PPU::drawTiles(uint16_t tileMapAddress, uint16_t tileDataAddress, uint8_t scanLine, uint8_t yPosition, bool usingWindow)
{
    uint16_t tileRow = static_cast<uint16_t>(yPosition / 8) * 32;
    uint8_t scrollX = this->mmu->getByte(SCX);
    uint8_t windowX = this->mmu->getByte(WX) - 7;

    // DMG
    uint8_t dmgPalette = this->mmu->getByte(BGP);

    for (uint8_t pixel = 0; pixel < 160; pixel++)
    {
        uint8_t xPosition = pixel;

        if (usingWindow && pixel >= windowX)
        {
            xPosition -= windowX;
        }
        else
        {
            xPosition += scrollX;
        }

        uint16_t tileColumn = static_cast<uint16_t>(xPosition / 8);
        uint8_t tileId = this->mmu->getByte(tileMapAddress + tileRow + tileColumn);
        uint16_t tileData = tileDataAddress;

        // http://bgb.bircd.org/pandocs.htm > VRAM Background Maps
        // Tile patterns are taken from the Tile Data Table located either at $8000-8FFF or $8800-97FF.
        // In the first case, patterns are numbered with unsigned numbers from 0 to 255 (i.e. pattern #0 lies at address $8000).
        // In the second case, patterns have signed numbers from -128 to 127 (i.e. pattern #0 lies at address $9000).
        // which means:
        //  - tileDataAddress == 0x8000 -> using UNsigned data
        //  - tileDataAddress == 0x8800 -> using signed data
        if (tileDataAddress == 0x8000)
        {
            tileData += tileId * 16;
        }
        else
        {
            tileData += static_cast<int8_t>((tileId + 128) * 16);
        }
    }

    // CGB
}

void PPU::drawObjects(ObjComposition objectComposition, uint8_t scanLine)
{
    //
}

}
