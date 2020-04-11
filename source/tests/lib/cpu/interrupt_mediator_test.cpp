#ifdef TESTING

#include "catch2/catch.hpp"
#include "lib/cpu/interrupt_mediator.hpp"

using namespace gb_lib;

SCENARIO( "InterruptMediator test", "[InterruptMediator]" ) {

    GIVEN( "InterruptMediator" ) {
        InterruptMediator interruptMediator;

        WHEN( "getIF" ) {
            interruptMediator.setIF(0);
            uint8_t ifValue1 = interruptMediator.getIF();

            interruptMediator.setIF(0x1F);
            uint8_t ifValue2 = interruptMediator.getIF();

            interruptMediator.setIF(0x07);
            uint8_t ifValue3 = interruptMediator.getIF();

            THEN( "the upper 3 bits(unused) should be 1" ) {
                REQUIRE( ifValue1 == 0xE0);
                REQUIRE( ifValue2 == 0xFF);
                REQUIRE( ifValue3 == 0xE7);
            }
        }
    }

    GIVEN( "Interrupt" ) {
        InterruptMediator interruptMediator;

        WHEN( "requestInterrupt" ) {
                interruptMediator.setIF(0);
                interruptMediator.requestInterrupt(Interrupt::VBLANK);
                uint8_t ifValue1 = interruptMediator.getIF();

                interruptMediator.setIF(0);
                interruptMediator.requestInterrupt(Interrupt::LCD);
                uint8_t ifValue2 = interruptMediator.getIF();

                interruptMediator.setIF(0);
                interruptMediator.requestInterrupt(Interrupt::TIMER);
                uint8_t ifValue3 = interruptMediator.getIF();

                interruptMediator.setIF(0);
                interruptMediator.requestInterrupt(Interrupt::SERIAL);
                uint8_t ifValue4 = interruptMediator.getIF();

                interruptMediator.setIF(0);
                interruptMediator.requestInterrupt(Interrupt::INPUT);
                uint8_t ifValue5 = interruptMediator.getIF();

            THEN( "the corresponding interrupt bit should be 1" ) {
                REQUIRE( ifValue1 == 0xE1);
                REQUIRE( ifValue2 == 0xE2);
                REQUIRE( ifValue3 == 0xE4);
                REQUIRE( ifValue4 == 0xE8);
                REQUIRE( ifValue5 == 0xF0);
            }
        }
    }

    GIVEN( "Interrupt" ) {
        InterruptMediator interruptMediator;

        WHEN( "requestInterrupt" ) {
                interruptMediator.setIF(0x1E);
                interruptMediator.requestInterrupt(Interrupt::VBLANK);
                uint8_t ifValue1 = interruptMediator.getIF();

                interruptMediator.setIF(0x1D);
                interruptMediator.requestInterrupt(Interrupt::LCD);
                uint8_t ifValue2 = interruptMediator.getIF();

                interruptMediator.setIF(0x1B);
                interruptMediator.requestInterrupt(Interrupt::TIMER);
                uint8_t ifValue3 = interruptMediator.getIF();

                interruptMediator.setIF(0x17);
                interruptMediator.requestInterrupt(Interrupt::SERIAL);
                uint8_t ifValue4 = interruptMediator.getIF();

                interruptMediator.setIF(0x0F);
                interruptMediator.requestInterrupt(Interrupt::INPUT);
                uint8_t ifValue5 = interruptMediator.getIF();

            THEN( "the other interrupt bits should not be affected" ) {
                REQUIRE( ifValue1 == 0xFF);
                REQUIRE( ifValue2 == 0xFF);
                REQUIRE( ifValue3 == 0xFF);
                REQUIRE( ifValue4 == 0xFF);
                REQUIRE( ifValue5 == 0xFF);
            }
        }
    }
}

#endif
