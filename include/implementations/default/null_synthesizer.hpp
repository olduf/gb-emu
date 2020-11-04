#pragma once

#include "lib/audio/synthesizer.hpp"

namespace gb_lib {

class NullSynthesizer : public Synthesizer
{
public:
  NullSynthesizer() = default;
  virtual ~NullSynthesizer() = default;

  void foo();
};

}
