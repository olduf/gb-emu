#ifndef _CGB_MEMORY_UNUSED_MEMORY_FEA0_FEFF_H_
#define _CGB_MEMORY_UNUSED_MEMORY_FEA0_FEFF_H_

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class CGBUnusedMemoryFEA0_FEFF : public MemorySpace
{
public:
    uint8_t getByte(uint16_t address);
    void setByte(uint16_t address, uint8_t value);

private:
    uint8_t memory[0x60] = {};
};

}

#endif
