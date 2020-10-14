#include <doctest/doctest.h>
#include "lib/cpu/interrupt_mediator.hpp"

using namespace gb_lib;

TEST_CASE("InterruptMediator test") {
    InterruptMediator interruptMediator;

    SUBCASE("when getIF, the upper 3 bits(unused) should be 1") {
        interruptMediator.setIF(0);
        uint8_t ifValue1 = interruptMediator.getIF();

        interruptMediator.setIF(0x1F);
        uint8_t ifValue2 = interruptMediator.getIF();

        interruptMediator.setIF(0x07);
        uint8_t ifValue3 = interruptMediator.getIF();

        CHECK(ifValue1 == 0xE0);
        CHECK(ifValue2 == 0xFF);
        CHECK(ifValue3 == 0xE7);
    }

    SUBCASE("given interrupt, when requestInterrupt, the corresponding interrupt bit should be 1") {
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

        CHECK(ifValue1 == 0xE1);
        CHECK(ifValue2 == 0xE2);
        CHECK(ifValue3 == 0xE4);
        CHECK(ifValue4 == 0xE8);
        CHECK(ifValue5 == 0xF0);
    }

    SUBCASE("given interrupt, when requestInterrupt, the other interrupt bits should not be affected") {
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

        CHECK(ifValue1 == 0xFF);
        CHECK(ifValue2 == 0xFF);
        CHECK(ifValue3 == 0xFF);
        CHECK(ifValue4 == 0xFF);
        CHECK(ifValue5 == 0xFF);
    }
}
