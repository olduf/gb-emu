#pragma once

#include <cstdint>
#include "lib/cpu/interrupt.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class InterruptMediator
{
public:
    uint8_t getIF();

    void setIF(uint8_t ifValue);

    void requestInterrupt(Interrupt interrupt);

private:
    uint8_t ifValue = 0;
};

}
