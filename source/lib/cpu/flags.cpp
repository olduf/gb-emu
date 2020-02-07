#include "lib/cpu/flags.hpp"

namespace gb_lib {

bool Flags::isZero()
{
    return BitUtil::getBit(this->value, FLAGS_ZERO_BIT);
}

Flags& Flags::setZero(bool zero)
{
    if (zero) {
        this->value = BitUtil::setBit(this->value, FLAGS_ZERO_BIT) & 0xF0;
    } else {
        this->value = BitUtil::clearBit(this->value, FLAGS_ZERO_BIT) & 0xF0;
    }

    return *this;
}

bool Flags::isSubtraction()
{
    return BitUtil::getBit(this->value, FLAGS_SUBTRACTION_BIT);
}

Flags& Flags::setSubtraction(bool subtraction)
{
    if (subtraction) {
        this->value = BitUtil::setBit(this->value, FLAGS_SUBTRACTION_BIT) & 0xF0;
    } else {
        this->value = BitUtil::clearBit(this->value, FLAGS_SUBTRACTION_BIT) & 0xF0;
    }

  return *this;
}

bool Flags::isHalfCarry()
{
    return BitUtil::getBit(this->value, FLAGS_HALF_CARRY_BIT);
}

Flags& Flags::setHalfCarry(bool halfCarry)
{
    if (halfCarry) {
        this->value = BitUtil::setBit(this->value, FLAGS_HALF_CARRY_BIT) & 0xF0;
    } else {
        this->value = BitUtil::clearBit(this->value, FLAGS_HALF_CARRY_BIT) & 0xF0;
    }

  return *this;
}

bool Flags::isCarry()
{
    return BitUtil::getBit(this->value, FLAGS_CARRY_BIT);
}

Flags& Flags::setCarry(bool carry)
{
    if (carry) {
        this->value = BitUtil::setBit(this->value, FLAGS_CARRY_BIT) & 0xF0;
    } else {
        this->value = BitUtil::clearBit(this->value, FLAGS_CARRY_BIT) & 0xF0;
    }

  return *this;
}

uint8_t Flags::getValue()
{
    return this->value;
}
void Flags::setValue(uint8_t value)
{
    this->value = value;
}

}
