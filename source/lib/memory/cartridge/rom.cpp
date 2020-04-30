#include "lib/memory/cartridge/rom.hpp"

namespace gb_lib {

Rom::Rom(uint8_t* data, uint32_t size)
{
    this->rom = data;
    this->size = size < 0x8000 ? size : 0x8000;
}

uint8_t Rom::getByte(uint16_t address)
{
    if (address < this->size) {
      return this->rom[address];
    } else {
      return 0xFF;
    }
}

}
