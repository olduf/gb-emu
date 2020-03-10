#ifndef _GRAPHIC_PPU_H_
#define _GRAPHIC_PPU_H_

#include "lib/graphic/obj_composition.hpp"
#include "lib/graphic/renderer.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class PPU
{
public:
    PPU(MemorySpace* mmu, Renderer* renderer);

    void drawScanLine(
        bool backgroundEnabled,
        bool objectEnabled,
        bool windowEnabled,
        ObjComposition objectComposition,
        uint16_t bgTileMapAddress,
        uint16_t tileDataAddress,
        uint16_t windowTileMapAddress,
        uint8_t scanLine);

private:
    void drawTiles(uint16_t tileMapAddress, uint16_t tileDataAddress, uint8_t scanLine, uint8_t yPosition, bool usingWindow);
    void drawObjects(ObjComposition objectComposition, uint8_t scanLine);

private:
    MemorySpace* mmu;
    Renderer* renderer;
    uint8_t buffer[160 * 144] = {};
};

}

#endif
