#ifdef TESTING

#include "catch2/catch.hpp"
#include "lib/timer/timer_util.hpp"

using namespace gb_lib;

SCENARIO( "TimerUtil test", "[TimerUtil]" ) {
    TimerUtil timerUtil;

    GIVEN( "bit 2 of tac is ONE" ) {
        uint8_t tac = 0x04;

        WHEN( "isTimerEnabled" ) {
            bool isTimerEnabled = timerUtil.isTimerEnabled(tac);

            THEN( "return true" ) {
                REQUIRE( isTimerEnabled == true);
            }
        }
    }

    GIVEN( "bit 2 of tac is ZERO" ) {
        uint8_t tac = 0;

        WHEN( "isTimerEnabled" ) {
            bool isTimerEnabled = timerUtil.isTimerEnabled(tac);

            THEN( "return false" ) {
                REQUIRE( isTimerEnabled == false);
            }
        }
    }

    GIVEN( "timer is disabled" ) {
        uint16_t div = 0xFFFF;
        uint8_t tac = 0;

        WHEN( "isTimaCircuitUp" ) {
            bool isTimaCircuitUp = timerUtil.isTimaCircuitUp(div, tac);

            THEN( "return false" ) {
                REQUIRE( isTimaCircuitUp == false);
            }
        }
    }

    GIVEN( "timer is enabled and selected timer bit is ZERO" ) {
        uint16_t div = 0;
        uint8_t tac1 = 0x04;
        uint8_t tac2 = 0x05;
        uint8_t tac3 = 0x06;
        uint8_t tac4 = 0x07;

        WHEN( "isTimaCircuitUp" ) {
            bool isTimaCircuitUp1 = timerUtil.isTimaCircuitUp(div, tac1);
            bool isTimaCircuitUp2 = timerUtil.isTimaCircuitUp(div, tac2);
            bool isTimaCircuitUp3 = timerUtil.isTimaCircuitUp(div, tac3);
            bool isTimaCircuitUp4 = timerUtil.isTimaCircuitUp(div, tac4);

            THEN( "return false" ) {
                REQUIRE( isTimaCircuitUp1 == false);
                REQUIRE( isTimaCircuitUp2 == false);
                REQUIRE( isTimaCircuitUp3 == false);
                REQUIRE( isTimaCircuitUp4 == false);
            }
        }
    }

    GIVEN( "bit 0-1 of tac are ZERO-ZERO" ) {
        uint8_t tac = 0xF8;

        WHEN( "isTimerEnabled" ) {
            uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

            THEN( "return 1024" ) {
                REQUIRE( timerFrequency == 1024);
            }
        }
    }

    GIVEN( "bit 0-1 of tac are ZERO-ONE" ) {
        uint8_t tac = 0xF9;

        WHEN( "isTimerEnabled" ) {
            uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

            THEN( "return 16" ) {
                REQUIRE( timerFrequency == 16);
            }
        }
    }

    GIVEN( "bit 0-1 of tac are ONE-ZERO" ) {
        uint8_t tac = 0xFA;

        WHEN( "isTimerEnabled" ) {
            uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

            THEN( "return 64" ) {
                REQUIRE( timerFrequency == 64);
            }
        }
    }

    GIVEN( "bit 0-1 of tac are ONE-ONE" ) {
        uint8_t tac = 0xFB;

        WHEN( "isTimerEnabled" ) {
            uint32_t timerFrequency = timerUtil.getTimerFrequency(tac);

            THEN( "return 256" ) {
                REQUIRE( timerFrequency == 256);
            }
        }
    }
}

#endif
