#ifndef _CPU_FLAGS_H_
#define _CPU_FLAGS_H_

#include <cstdint>
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class Flags
{
public:
    bool isZero();
    Flags& setZero(bool zero);

    bool isSubtraction();
    Flags& setSubtraction(bool subtraction);

    bool isHalfCarry();
    Flags& setHalfCarry(bool halfCarry);

    bool isCarry();
    Flags& setCarry(bool carry);

    uint8_t getValue();
    void setValue(uint8_t value);

private:
    uint8_t value;

private:
    const uint8_t FLAGS_ZERO_BIT = 7;
    const uint8_t FLAGS_SUBTRACTION_BIT = 6;
    const uint8_t FLAGS_HALF_CARRY_BIT = 5;
    const uint8_t FLAGS_CARRY_BIT = 4;
};

}

#endif
