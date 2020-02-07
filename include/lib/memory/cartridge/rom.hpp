#ifndef _MEMORY_CARTRIDGE_ROM_H_
#define _MEMORY_CARTRIDGE_ROM_H_

#include <cstring>
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class Rom : public MemorySpace
{
public:
    Rom(uint8_t* data, uint32_t size);

    uint8_t getByte(uint16_t address);

private:
    uint8_t rom[0x8000] = {};
};

}

#endif
