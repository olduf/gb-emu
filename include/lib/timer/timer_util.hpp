#pragma once

#include <cstdint>
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class TimerUtil
{
public:
    bool isTimerEnabled(uint8_t tac);
    bool isTimaCircuitUp(uint16_t div, uint8_t tac);
    uint32_t getTimerFrequency(uint8_t tac);

private:
    const uint32_t timerFrequencies[4] = { 1024, 16, 64, 256 };
};

}
