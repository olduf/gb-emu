#ifndef _MEMORY_LOCATION_H_
#define _MEMORY_LOCATION_H_

#include <cstdint>

namespace gb_lib {
    // Interrupt handler
    const uint16_t VBLANK_INTERRUPT_HANDLER = 0x0040;
    const uint16_t LCD_INTERRUPT_HANDLER = 0x0048;
    const uint16_t TIMER_INTERRUPT_HANDLER = 0x0050;
    const uint16_t SERIAL_INTERRUPT_HANDLER = 0x0058;
    const uint16_t INPUT_INTERRUPT_HANDLER = 0x0060;

    // Control registers
    const uint16_t P1 = 0xFF00;
    const uint16_t SB = 0xFF01;
    const uint16_t SC = 0xFF02;

    // Divider
    const uint16_t DIV = 0xFF04; // <-- writing will reset value to zero

    // Timer
    const uint16_t TIMA = 0xFF05;

    // Timer modulo
    const uint16_t TMA = 0xFF06;

    // Timer control
    // Bit 7 - Not used
    // Bit 6 - Not used
    // Bit 5 - Not used
    // Bit 4 - Not used
    // Bit 3 - Not used
    // Bit 2 - Timer stop (0: stop, 1: operate)
    // Bit 1-0 - Timer frequency (see below) (f = 4194304 in NORMAL speed, f = 8388608 in DOUBLE speed)
    //       0: f / 2^10
    //       1: f / 2^4
    //       2: f / 2^6
    //       3: f / 2^8
    const uint16_t TAC = 0xFF07;

    // Interupt request flag
    // Bit 7 - Not used
    // Bit 6 - Not used
    // Bit 5 - Not used
    // Bit 4 - Input
    // Bit 3 - Serial
    // Bit 2 - Timer
    // Bit 1 - LCD
    // Bit 0 - VBLANK
    const uint16_t IF = 0xFF0F;

    // LCD Control
    // Bit 7 - LCD Display Enable             (0=Off, 1=On)
    // Bit 6 - Window Tile Map Display Select (0=9800-9BFF, 1=9C00-9FFF)
    // Bit 5 - Window Display Enable          (0=Off, 1=On)
    // Bit 4 - BG & Window Tile Data Select   (0=8800-97FF, 1=8000-8FFF)
    // Bit 3 - BG Tile Map Display Select     (0=9800-9BFF, 1=9C00-9FFF)
    // Bit 2 - OBJ (Sprite) Size              (0=8x8, 1=8x16)
    // Bit 1 - OBJ (Sprite) Display Enable    (0=Off, 1=On)
    // Bit 0 - BG/Window Display/Priority     (0=Off, 1=On)
    const uint16_t LCDC = 0xFF40;

    // LCD Status
    // Bit 7 - Not used
    // Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
    // Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
    // Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
    // Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
    // Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
    // Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
    //       0: During H-Blank
    //       1: During V-Blank
    //       2: During Searching OAM
    //       3: During Transferring Data to LCD Driver
    const uint16_t STAT = 0xFF41;

    // Scroll Y
    const uint16_t SCY = 0xFF42;

    // Scroll X
    const uint16_t SCX = 0xFF43;

    // Current Scanline - [0 - 153] - 144 and up means VBLANK
    const uint16_t LY = 0xFF44; // <-- writing will reset value to 0

    // LY compare - can be used to trigger interrupt when current scanline is at this value
    const uint16_t LYC = 0xFF45;
    const uint16_t DMA = 0xFF46;
    const uint16_t BGP = 0xFF47;
    const uint16_t OBP0 = 0xFF48;
    const uint16_t OBP1 = 0xFF49;
    const uint16_t WY = 0xFF4A;
    const uint16_t WX = 0xFF4B;

    const uint16_t KEY1 = 0xFF4D;

    const uint16_t VBK = 0xFF4F;

    const uint16_t HDMA1 = 0xFF51;
    const uint16_t HDMA2 = 0xFF52;
    const uint16_t HDMA3 = 0xFF53;
    const uint16_t HDMA4 = 0xFF54;
    const uint16_t HDMA5 = 0xFF55;
    const uint16_t RP = 0xFF56;

    const uint16_t BCPS = 0xFF68;
    const uint16_t BCPB = 0xFF69;
    const uint16_t OCPS = 0xFF6A;
    const uint16_t OCPB = 0xFF6B;

    const uint16_t SBVK = 0xFF70;

    const uint16_t IE = 0xFFFF;
}

#endif