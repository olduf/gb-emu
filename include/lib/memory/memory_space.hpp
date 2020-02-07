#ifndef _MEMORY_SPACE_H_
#define _MEMORY_SPACE_H_

#include <cstdint>

namespace gb_lib {

class MemorySpace
{
public:
  virtual ~MemorySpace() = default;

  virtual uint8_t getByte(uint16_t address) = 0;

  virtual void setByte(uint16_t address, uint8_t value);
  virtual void setByteInternal(uint16_t address, uint8_t value);
};

}

#endif
