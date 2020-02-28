#ifndef _MEMORY_UNUSED_MEMORY_FEA0_FEFF_H_
#define _MEMORY_UNUSED_MEMORY_FEA0_FEFF_H_

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class UnusedMemoryFEA0_FEFF : public MemorySpace
{
public:
    uint8_t getByte(uint16_t address);
};

}

#endif
