#pragma once

#include "lib/memory/memory_space_decorator.hpp"

namespace gb_lib {

class NullMMUDecorator : public MemorySpaceDecorator
{
public:
  NullMMUDecorator() = default;
  virtual ~NullMMUDecorator() = default;

  uint8_t getByte(uint16_t address);
  uint8_t getByteInternal(uint16_t address);

  void setByte(uint16_t address, uint8_t value);
  void setByteInternal(uint16_t address, uint8_t value);
};

}
