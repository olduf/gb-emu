#ifdef TESTING

#include "catch2/catch.hpp"
#include "lib/timer/set_tac_auditor.hpp"

using namespace gb_lib;

SCENARIO( "SetTacAuditor", "[SetTacAuditor]" ) {
    TimerUtil timerUtil;
    SetTacAuditor setTacAuditor(&timerUtil);

    GIVEN( "timer is disabled in old TAC value" ) {
        uint16_t divValue = 0;
        uint8_t oldTacValue = 0;
        uint8_t newTacValue = 0x04;

        WHEN( "needToIncreaseTima" ) {
            bool needToIncreaseTima = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue);

            THEN( "return true" ) {
                REQUIRE( needToIncreaseTima == false);
            }
        }
    }

    GIVEN( "disabling timer when old selected bit ONE" ) {
        uint16_t divValue = 0x0200;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0;
        uint8_t newTacValue2 = 0x01;
        uint8_t newTacValue3 = 0x02;
        uint8_t newTacValue4 = 0x03;

        WHEN( "needToIncreaseTima" ) {
            bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
            bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
            bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);
            bool needToIncreaseTima4 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue4);

            THEN( "return true" ) {
                REQUIRE( timerUtil.isTimerEnabled(oldTacValue) == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue1) == false);
                REQUIRE( needToIncreaseTima1 == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue2) == false);
                REQUIRE( needToIncreaseTima2 == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue3) == false);
                REQUIRE( needToIncreaseTima3 == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue4) == false);
                REQUIRE( needToIncreaseTima4 == true);
            }
        }
    }

    GIVEN( "disabling timer when old selected bit ZERO" ) {
        uint16_t divValue = 0x0100;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0;
        uint8_t newTacValue2 = 0x01;
        uint8_t newTacValue3 = 0x02;
        uint8_t newTacValue4 = 0x03;

        WHEN( "needToIncreaseTima" ) {
            bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
            bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
            bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);
            bool needToIncreaseTima4 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue4);

            THEN( "return false" ) {
                REQUIRE( timerUtil.isTimerEnabled(oldTacValue) == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue1) == false);
                REQUIRE( needToIncreaseTima1 == false);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue2) == false);
                REQUIRE( needToIncreaseTima2 == false);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue3) == false);
                REQUIRE( needToIncreaseTima3 == false);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue4) == false);
                REQUIRE( needToIncreaseTima4 == false);
            }
        }
    }

    GIVEN( "changing timer frequency when old selected bit ONE and new selected bit is ZERO" ) {
        uint16_t divValue = 0x0200;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0x05;
        uint8_t newTacValue2 = 0x06;
        uint8_t newTacValue3 = 0x07;

        WHEN( "needToIncreaseTima" ) {
            bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
            bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
            bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);

            THEN( "return true" ) {
                REQUIRE( timerUtil.isTimerEnabled(oldTacValue) == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue1) == true);
                REQUIRE( needToIncreaseTima1 == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue2) == true);
                REQUIRE( needToIncreaseTima2 == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue3) == true);
                REQUIRE( needToIncreaseTima3 == true);
            }
        }
    }

    GIVEN( "changing timer frequency when old selected bit ONE and new selected bit is ONE" ) {
        uint16_t divValue = 0xFFFF;
        uint8_t oldTacValue = 0x04;
        uint8_t newTacValue1 = 0x05;
        uint8_t newTacValue2 = 0x06;
        uint8_t newTacValue3 = 0x07;

        WHEN( "needToIncreaseTima" ) {
            bool needToIncreaseTima1 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue1);
            bool needToIncreaseTima2 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue2);
            bool needToIncreaseTima3 = setTacAuditor.needToIncreaseTima(divValue, oldTacValue, newTacValue3);

            THEN( "return false" ) {
                REQUIRE( timerUtil.isTimerEnabled(oldTacValue) == true);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue1) == true);
                REQUIRE( needToIncreaseTima1 == false);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue2) == true);
                REQUIRE( needToIncreaseTima2 == false);

                REQUIRE( timerUtil.isTimerEnabled(newTacValue3) == true);
                REQUIRE( needToIncreaseTima3 == false);
            }
        }
    }
}

#endif
