#pragma once

#include "lib/cpu/speed_mode.hpp"
#include "lib/memory/memory_space.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class SpeedModeHandler
{
public:
    SpeedModeHandler(MemorySpace* mmu);

    SpeedMode getSpeedMode();

    void handleSpeedMode();

private:
    MemorySpace* mmu;
    SpeedMode speedMode;
};

}
