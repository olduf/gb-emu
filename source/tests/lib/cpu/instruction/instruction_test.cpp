#ifdef TESTING

#include "catch2/catch.hpp"
#include "catch2/test_memory_space.hpp"
#include "lib/cpu/instructions.hpp"

using namespace gb_lib;

SCENARIO( "Instructions test", "[Instructions]" ) {
    Registers registers;
    TestMemorySpace memorySpace;

    GIVEN( "ADD SP,n instruction" ) {
        registers.setAF(0x1200);
        registers.setBC(0x5691);
        registers.setDE(0x9ABC);
        registers.setHL(0x0000);
        registers.setSP(0x0000);
        registers.setPC(0xDEF8);
        registers.setIME(false);

        memorySpace.setByte(0xDEF8, 0xE8);
        memorySpace.setByte(0xDEF9, 0xFF);

        uint16_t expectedAF = 0x1200;
        uint16_t expectedBC = 0x5691;
        uint16_t expectedDE = 0x9ABC;
        uint16_t expectedHL = 0x0000;
        uint16_t expectedSP = 0xFFFF;
        uint16_t expectedPC = 0xDEFA;
        bool expectedIME = false;

        Instruction* ADD_SP_n = instructions[0][0xE8];

        WHEN( "execute" ) {
            ADD_SP_n->execute(&registers, &memorySpace, 0);

            THEN( "right value is stored in SP, flags correctly set" ) {
                REQUIRE( registers.getAF() == expectedAF);
                REQUIRE( registers.getBC() == expectedBC);
                REQUIRE( registers.getDE() == expectedDE);
                REQUIRE( registers.getHL() == expectedHL);
                REQUIRE( registers.getSP() == expectedSP);
                REQUIRE( registers.getPC() == expectedPC);
                REQUIRE( registers.isIME() == expectedIME);
            }
        }
    }

    GIVEN( "CPL instruction" ) {
      registers.setAF(0x0000);
      registers.setBC(0x0001);
      registers.setDE(0x1F7F);
      registers.setHL(0x0F10);
      registers.setSP(0xDFF1);
      registers.setPC(0xDEF8);
      registers.setIME(false);

      memorySpace.setByte(0xDEF8, 0xE8);
      memorySpace.setByte(0xDEF9, 0xFF);

      uint16_t expectedAF = 0xFF60;
      uint16_t expectedBC = 0x0001;
      uint16_t expectedDE = 0x1F7F;
      uint16_t expectedHL = 0x0F10;
      uint16_t expectedSP = 0xDFF1;
      uint16_t expectedPC = 0xDEF9;
      bool expectedIME = false;

      Instruction* CPL = instructions[0][0x2F];

      WHEN( "execute" ) {
          CPL->execute(&registers, &memorySpace, 0);

          THEN( "right value is stored in SP, flags correctly set" ) {
              REQUIRE( registers.getAF() == expectedAF);
              REQUIRE( registers.getBC() == expectedBC);
              REQUIRE( registers.getDE() == expectedDE);
              REQUIRE( registers.getHL() == expectedHL);
              REQUIRE( registers.getSP() == expectedSP);
              REQUIRE( registers.getPC() == expectedPC);
              REQUIRE( registers.isIME() == expectedIME);
          }
      }
    }
}

#endif
