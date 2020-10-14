#include <doctest/doctest.h>
#include "lib/util/bit_util.hpp"

using namespace gb_lib;

TEST_CASE("BitUtil test") {
    uint8_t value = 0xF0;

    SUBCASE("when checking bit, the right value is returned") {
        CHECK(BitUtil::getBit(value, 0) == false);
        CHECK(BitUtil::getBit(value, 1) == false);
        CHECK(BitUtil::getBit(value, 2) == false);
        CHECK(BitUtil::getBit(value, 3) == false);
        CHECK(BitUtil::getBit(value, 4) == true);
        CHECK(BitUtil::getBit(value, 5) == true);
        CHECK(BitUtil::getBit(value, 6) == true);
        CHECK(BitUtil::getBit(value, 7) == true);
    }

    SUBCASE("when setting bit, the right value is returned") {
        CHECK(BitUtil::setBit(value, 0) == 0xF1);
        CHECK(BitUtil::setBit(value, 1) == 0xF2);
        CHECK(BitUtil::setBit(value, 2) == 0xF4);
        CHECK(BitUtil::setBit(value, 3) == 0xF8);
        CHECK(BitUtil::setBit(value, 4) == 0xF0);
        CHECK(BitUtil::setBit(value, 5) == 0xF0);
        CHECK(BitUtil::setBit(value, 6) == 0xF0);
        CHECK(BitUtil::setBit(value, 7) == 0xF0);
    }

    SUBCASE("when clearing bit, the right value is returned") {
        CHECK(BitUtil::clearBit(value, 0) == 0xF0);
        CHECK(BitUtil::clearBit(value, 1) == 0xF0);
        CHECK(BitUtil::clearBit(value, 2) == 0xF0);
        CHECK(BitUtil::clearBit(value, 3) == 0xF0);
        CHECK(BitUtil::clearBit(value, 4) == 0xE0);
        CHECK(BitUtil::clearBit(value, 5) == 0xD0);
        CHECK(BitUtil::clearBit(value, 6) == 0xB0);
        CHECK(BitUtil::clearBit(value, 7) == 0x70);
    }

    SUBCASE("when toggling bit, the right value is returned") {
        CHECK(BitUtil::toggleBit(value, 0) == 0xF1);
        CHECK(BitUtil::toggleBit(value, 1) == 0xF2);
        CHECK(BitUtil::toggleBit(value, 2) == 0xF4);
        CHECK(BitUtil::toggleBit(value, 3) == 0xF8);
        CHECK(BitUtil::toggleBit(value, 4) == 0xE0);
        CHECK(BitUtil::toggleBit(value, 5) == 0xD0);
        CHECK(BitUtil::toggleBit(value, 6) == 0xB0);
        CHECK(BitUtil::toggleBit(value, 7) == 0x70);
    }
}
