#pragma once

#pragma once

#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class MemorySpaceDecorator : public MemorySpace
{
public:
  MemorySpaceDecorator() = default;
  virtual ~MemorySpaceDecorator() = default;

  void setMemorySpace(MemorySpace* memorySpace);

protected:
  MemorySpace* memorySpace = nullptr;
};

}
