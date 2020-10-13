#pragma once

#include <cstdint>

namespace gb_lib {

enum class LCDMode : uint8_t
{
    HBLANK = 0,        // 204 cpu cycles
    VBLANK = 1,        // 4560 cpu cycles
    OAM_SEARCH = 2,    // 80 cpy cycles
    PIXEL_TRANSFER = 3 // 172 cpu cycles
};

}
