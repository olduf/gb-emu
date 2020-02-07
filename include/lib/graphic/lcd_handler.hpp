#ifndef _PPU_LCD_HANDLER_H_
#define _PPU_LCD_HANDLER_H_

#include <cstdint>

#include "lib/cpu/interrupt_handler.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/mmu.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

enum class LCDMode : uint8_t
{
    HBLANK = 0,        // 204 cpu cycles
    VBLANK = 1,        // 4560 cpu cycles
    OAM_SEARCH = 2,    // 80 cpy cycles
    PIXEL_TRANSFER = 3 // 172 cpu cycles
};

enum class ObjComposition : uint8_t
{
    BLOCK_8_BY_8 = 0,
    BLOCK_8_BY_16 = 4
};

class LCDHandler
{
public:
    LCDHandler(InterruptHandler* interruptHandler, MMU* mmu, bool isCGB);

    void updateLCD(uint32_t consumedCpuCycle);

private:
    bool isCGB;
    InterruptHandler* interruptHandler;
    MMU* mmu;
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
