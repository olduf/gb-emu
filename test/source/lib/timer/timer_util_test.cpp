#include <doctest/doctest.h>
#include "lib/timer/timer_util.hpp"

using namespace gb_lib;

TEST_CASE("TimerUtil test") {
    TimerUtil timerUtil;

    SUBCASE("given bit 2 of tac is ONE, when isTimerEnabled, then return true") {
        uint8_t tac = 0x04;

        bool isTimerEnabled = timerUtil.isTimerEnabled(tac);

        CHECK(isTimerEnabled == true);
    }

    SUBCASE("given bit 2 of tac is ZERO, when isTimerEnabled, then return false") {
      uint8_t tac = 0;

      bool isTimerEnabled = timerUtil.isTimerEnabled(tac);

      CHECK(isTimerEnabled == false);
    }

    SUBCASE("given timer is disabled, when isTimaCircuitUp, then return false") {
        uint16_t div = 0xFFFF;
        uint8_t tac = 0;

        bool isTimaCircuitUp = timerUtil.isTimaCircuitUp(div, tac);

        CHECK(isTimaCircuitUp == false);
    }

    SUBCASE("given bit 2 of tac is ZERO, when isTimerEnabled, then return false") {
        uint16_t div = 0;
        uint8_t tac1 = 0x04;
        uint8_t tac2 = 0x05;
        uint8_t tac3 = 0x06;
        uint8_t tac4 = 0x07;

        bool isTimaCircuitUp1 = timerUtil.isTimaCircuitUp(div, tac1);
        bool isTimaCircuitUp2 = timerUtil.isTimaCircuitUp(div, tac2);
        bool isTimaCircuitUp3 = timerUtil.isTimaCircuitUp(div, tac3);
        bool isTimaCircuitUp4 = timerUtil.isTimaCircuitUp(div, tac4);

        CHECK(isTimaCircuitUp1 == false);
        CHECK(isTimaCircuitUp2 == false);
        CHECK(isTimaCircuitUp3 == false);
        CHECK(isTimaCircuitUp4 == false);
    }

    SUBCASE("given bit 0-1 of tac are ZERO-ZERO, when getTimerFrequency, then return 1024") {
      uint8_t tac = 0xF8;

      uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

      CHECK(timerFrequency == 1024);
    }

    SUBCASE("given bit 0-1 of tac are ZERO-ONE, when getTimerFrequency, then return 16") {
      uint8_t tac = 0xF9;

      uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

      CHECK(timerFrequency == 16);
    }

    SUBCASE("given bit 0-1 of tac are ONE-ZERO, when getTimerFrequency, then return 64") {
      uint8_t tac = 0xFA;

      uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

      CHECK(timerFrequency == 64);
    }

    SUBCASE("given bit 0-1 of tac are ONE-ONE, when getTimerFrequency, then return 256") {
      uint8_t tac = 0xFB;

      uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

      CHECK(timerFrequency == 256);
    }
}
