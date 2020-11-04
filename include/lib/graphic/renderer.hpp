#pragma once

#include <cstdint>

namespace gb_lib {

class Renderer
{
public:
  virtual void foo() = 0;
  virtual ~Renderer() = default;
};

}
