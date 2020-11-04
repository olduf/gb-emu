#pragma once

#include "lib/graphic/renderer.hpp"

namespace gb_lib {

class ConsoleRenderer : public Renderer
{
public:
  ConsoleRenderer() = default;
  virtual ~ConsoleRenderer() = default;

  void foo();
};

}
