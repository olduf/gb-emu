// #ifdef TESTING
//
// #include "catch2/catch.hpp"
// #include "lib/util/bit_util.hpp"
//
// SCENARIO( "BitUtil tests", "[BitUtil]" ) {
//
//     GIVEN( "uint8_t value" ) {
//         uint8_t value = 0xF0;
//
//         WHEN( "checking bit" ) {
//             bool bit_0 = BitUtil::getBit(value, 0);
//             bool bit_1 = BitUtil::getBit(value, 1);
//             bool bit_2 = BitUtil::getBit(value, 2);
//             bool bit_3 = BitUtil::getBit(value, 3);
//             bool bit_4 = BitUtil::getBit(value, 4);
//             bool bit_5 = BitUtil::getBit(value, 5);
//             bool bit_6 = BitUtil::getBit(value, 6);
//             bool bit_7 = BitUtil::getBit(value, 7);
//
//             THEN( "the right values are returned" ) {
//                 REQUIRE( bit_0 == false );
//                 REQUIRE( bit_1 == false );
//                 REQUIRE( bit_2 == false );
//                 REQUIRE( bit_3 == false );
//                 REQUIRE( bit_4 == true );
//                 REQUIRE( bit_5 == true );
//                 REQUIRE( bit_6 == true );
//                 REQUIRE( bit_7 == true );
//             }
//         }
//
//         WHEN( "setting bit" ) {
//             THEN( "the right values is returned" ) {
//                 REQUIRE( BitUtil::setBit(value, 0) == 0xF1 );
//                 REQUIRE( BitUtil::setBit(value, 1) == 0xF2 );
//                 REQUIRE( BitUtil::setBit(value, 2) == 0xF4 );
//                 REQUIRE( BitUtil::setBit(value, 3) == 0xF8 );
//                 REQUIRE( BitUtil::setBit(value, 4) == 0xF0 );
//                 REQUIRE( BitUtil::setBit(value, 5) == 0xF0 );
//                 REQUIRE( BitUtil::setBit(value, 6) == 0xF0 );
//                 REQUIRE( BitUtil::setBit(value, 7) == 0xF0 );
//             }
//         }
//
//         WHEN( "clearing bit" ) {
//             THEN( "the right values is returned" ) {
//                 REQUIRE( BitUtil::clearBit(value, 0) == 0xF0 );
//                 REQUIRE( BitUtil::clearBit(value, 1) == 0xF0 );
//                 REQUIRE( BitUtil::clearBit(value, 2) == 0xF0 );
//                 REQUIRE( BitUtil::clearBit(value, 3) == 0xF0 );
//                 REQUIRE( BitUtil::clearBit(value, 4) == 0xE0 );
//                 REQUIRE( BitUtil::clearBit(value, 5) == 0xD0 );
//                 REQUIRE( BitUtil::clearBit(value, 6) == 0xB0 );
//                 REQUIRE( BitUtil::clearBit(value, 7) == 0x70 );
//             }
//         }
//     }
// }
//
// #endif
