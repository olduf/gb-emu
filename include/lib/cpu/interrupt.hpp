#ifndef _CPU_INTERRUPT_H_
#define _CPU_INTERRUPT_H_

#include <cstdint>

namespace gb_lib {

enum class Interrupt : uint8_t
{
    VBLANK = 0,
    LCD = 1,
    TIMER = 2,
    SERIAL = 3,
    INPUT = 4
};

}

#endif
