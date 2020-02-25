#ifndef _PPU_LCD_HANDLER_H_
#define _PPU_LCD_HANDLER_H_

#include <cstdint>

#include "lib/cpu/interrupt_handler.hpp"
#include "lib/graphic/lcd_mode.hpp"
#include "lib/graphic/obj_composition.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class LCDHandler
{
public:
    LCDHandler(InterruptHandler* interruptHandler, MemorySpace* mmu, bool isCGB);

    void updateLCD(uint32_t consumedCpuCycle);

private:
    bool isCGB;
    InterruptHandler* interruptHandler;
    MemorySpace* mmu;
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

    LCDMode getLCDMode(uint8_t stat);
    void setLCDMode(uint8_t stat, LCDMode lcdMode);

    void handleLCDStatus();
};

}

#endif
