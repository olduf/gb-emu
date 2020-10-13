#pragma once

#include <cstdint>

#include "lib/cpu/interrupt_handler.hpp"
#include "lib/graphic/lcd_status_util.hpp"
#include "lib/graphic/obj_composition.hpp"
#include "lib/graphic/ppu.hpp"

namespace gb_lib {

class LCDHandler
{
public:
    LCDHandler(InterruptHandler* interruptHandler, MemorySpace* ioRegisters, PPU* ppu, bool isCGB);

    void updateLCD(uint32_t consumedCpuCycle);

private:
    bool isCGB;
    InterruptHandler* interruptHandler;
    MemorySpace* ioRegisters;
    PPU* ppu;
    uint32_t cpuCycle;

private:
    const uint32_t cyclePerScanLine = 456;
    const uint32_t oamSearchMaxCycle = 80;
    const uint32_t pixelTransferMaxCycle = 252;

private:
    bool areBackgroundEnabled(uint8_t lcdc);
    bool areOBJEnabled(uint8_t lcdc);
    bool areWindowEnabled(uint8_t lcdc);
    bool isLCDEnabled(uint8_t lcdc);
    ObjComposition getObjComposition(uint8_t lcdc);
    uint16_t getBackgroundTileMapAddress(uint8_t lcdc);
    uint16_t getTileDataAddress(uint8_t lcdc);
    uint16_t getWindowTileMapAddress(uint8_t lcdc);

    void handleLCDStatus();
};

}
