#ifdef TESTING
//
// #include "lib/catch2/catch.hpp"
// #include "lib/cpu/instruction/op/alu/xor_bytes.hpp"
//
// SCENARIO( "XorBytes tests", "[XorBytes]" ) {
//     int32_tcombinedBytes;
//     Registers registers;
//     MMU mmu;
//
//     XorBytes xorBytes(&InstructionArgument::A);
//
//     GIVEN( "context and operand" ) {
//         uint32_t expected = 0x16;
//         uint32_t value = 0x94;
//         registers.setA(0x82);
//
//         WHEN( "execute" ) {
//             uint32_t result = xorBytes.execute(registers, mmu, combinedBytes, value);
//
//             THEN( "the right value is returned" ) {
//                 REQUIRE( (result & 0xFF) == expected);
//             }
//         }
//     }
//
//     GIVEN( "context and operand" ) {
//         registers.getFlags().setSubtraction(true);
//         registers.getFlags().setHalfCarry(true);
//         registers.getFlags().setCarry(true);
//
//         uint32_t expected = 0xFF;
//         uint32_t value = 0xF0;
//         registers.setA(0x0F);
//
//         WHEN( "execute" ) {
//             uint32_t result = xorBytes.execute(registers, mmu, combinedBytes, value);
//
//             THEN( "subtraction, half-carry and carry flags are true" ) {
//                 REQUIRE( (result & 0xFF) == expected);
//                 REQUIRE( registers.getFlags().isSubtraction() == false );
//                 REQUIRE( registers.getFlags().isHalfCarry() == false );
//                 REQUIRE( registers.getFlags().isCarry() == false );
//             }
//         }
//     }
//
//     GIVEN( "result is zero" ) {
//         registers.getFlags().setZero(false);
//
//         uint32_t expected = 0;
//         uint32_t value = 0xF3;
//         registers.setA(0xF3);
//
//         WHEN( "execute" ) {
//             uint32_t result = xorBytes.execute(registers, mmu, combinedBytes, value);
//
//             THEN( "zero flag is true" ) {
//                 REQUIRE( (result & 0xFF) == expected);
//                 REQUIRE( registers.getFlags().isZero() == true );
//             }
//         }
//     }
//
//     GIVEN( "result is not zero" ) {
//         registers.getFlags().setZero(true);
//
//         uint32_t expected = 0x3E;
//         uint32_t value = 0x0F;
//         registers.setA(0x31);
//
//         WHEN( "execute" ) {
//             uint32_t result = xorBytes.execute(registers, mmu, combinedBytes, value);
//
//             THEN( "zero flag is false" ) {
//                 REQUIRE( (result & 0xFF) == expected);
//                 REQUIRE( registers.getFlags().isZero() == false );
//             }
//         }
//     }
// }

#endif
