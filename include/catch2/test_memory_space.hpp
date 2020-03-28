#ifdef TESTING

#include "lib/memory/memory_space.hpp"

using namespace gb_lib;

class TestMemorySpace : public MemorySpace
{
public:
  uint8_t getByte(uint16_t address)
  {
      return this->memory[address];
  }

  uint8_t getByteInternal(uint16_t address)
  {
      return this->memory[address];
  }

  void setByte(uint16_t address, uint8_t value)
  {
      this->memory[address] = value;
  }

  void setByteInternal(uint16_t address, uint8_t value)
  {
      this->memory[address] = value;
  }

private:
    uint8_t memory[0xFFFF] = {};
};

#endif
