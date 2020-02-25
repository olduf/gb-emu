#ifndef _GRAPHIC_PPU_H_
#define _GRAPHIC_PPU_H_

#include "lib/graphic/renderer.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class PPU
{
public:
    void drawScanLine(uint8_t scanLine);

private:
    MemorySpace* mmu;
    Renderer* renderer;
};

}

#endif
