#include <doctest/doctest.h>
#include "lib/timer/set_tac_auditor.hpp"

using namespace gb_lib;

TEST_CASE("SetTacAuditor test") {
  TimerUtil timerUtil;
  SetTacAuditor setTacAuditor(&timerUtil);

    SUBCASE("given timer is disabled in old TAC value, when needToIncreaseTima, the return false") {
        uint16_t divValue = 0;
        uint8_t oldTacValue = 0;
        uint8_t newTacValue = 0x04;

        bool needToIncreaseTima = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue);

        CHECK(needToIncreaseTima == false);
    }

    SUBCASE("given timer is disabled when old selected bit is ONE, when needToIncreaseTima, the return true") {
        uint16_t divValue = 0x0200;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0;
        uint8_t newTacValue2 = 0x01;
        uint8_t newTacValue3 = 0x02;
        uint8_t newTacValue4 = 0x03;

        bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
        bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
        bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);
        bool needToIncreaseTima4 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue4);

        CHECK(timerUtil.isTimerEnabled(oldTacValue) == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue1) == false);
        CHECK(needToIncreaseTima1 == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue2) == false);
        CHECK(needToIncreaseTima2 == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue3) == false);
        CHECK(needToIncreaseTima3 == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue4) == false);
        CHECK(needToIncreaseTima4 == true);
    }

    SUBCASE("given timer is disabled when old selected bit is ZERO, when needToIncreaseTima, the return false") {
        uint16_t divValue = 0x0100;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0;
        uint8_t newTacValue2 = 0x01;
        uint8_t newTacValue3 = 0x02;
        uint8_t newTacValue4 = 0x03;

        bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
        bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
        bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);
        bool needToIncreaseTima4 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue4);

        CHECK(timerUtil.isTimerEnabled(oldTacValue) == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue1) == false);
        CHECK(needToIncreaseTima1 == false);

        CHECK(timerUtil.isTimerEnabled(newTacValue2) == false);
        CHECK(needToIncreaseTima2 == false);

        CHECK(timerUtil.isTimerEnabled(newTacValue3) == false);
        CHECK(needToIncreaseTima3 == false);

        CHECK(timerUtil.isTimerEnabled(newTacValue4) == false);
        CHECK(needToIncreaseTima4 == false);
    }

    SUBCASE("given timer frequency is changeded when old selected bit is ONE and new selected bit is ZERO, when needToIncreaseTima, the return true") {
        uint16_t divValue = 0x0200;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0x05;
        uint8_t newTacValue2 = 0x06;
        uint8_t newTacValue3 = 0x07;

        bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
        bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
        bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);

        CHECK(timerUtil.isTimerEnabled(oldTacValue) == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue1) == true);
        CHECK(needToIncreaseTima1 == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue2) == true);
        CHECK(needToIncreaseTima2 == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue3) == true);
        CHECK(needToIncreaseTima3 == true);
    }

    SUBCASE("given timer frequency is changeded when old selected bit is ONE and new selected bit is ONE, when needToIncreaseTima, the return false") {
        uint16_t divValue = 0xFFFF;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0x05;
        uint8_t newTacValue2 = 0x06;
        uint8_t newTacValue3 = 0x07;

        bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
        bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
        bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);

        CHECK(timerUtil.isTimerEnabled(oldTacValue) == true);

        CHECK(timerUtil.isTimerEnabled(newTacValue1) == true);
        CHECK(needToIncreaseTima1 == false);

        CHECK(timerUtil.isTimerEnabled(newTacValue2) == true);
        CHECK(needToIncreaseTima2 == false);

        CHECK(timerUtil.isTimerEnabled(newTacValue3) == true);
        CHECK(needToIncreaseTima3 == false);
    }
}
