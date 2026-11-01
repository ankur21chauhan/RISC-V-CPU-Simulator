#include "alu.hpp"

#include<cassert>
#include<cstdint>
#include<iostream>
#include<limits>

int main(){
    ALU alu;

    //Test1: Addition
    assert(alu.add(42, 99) == 141);

    //Test2: Subtraction
    assert(alu.sub(99, 42) == 57);

    //Test3 : Result is ZERO
    assert(alu.sub(42, 42) == 0);

    //Test4 : Addition with ZERO
    assert(alu.add(42, 0) == 42);

    //Test5 : Unsigned 32-bit wraparound
    assert(alu.sub(0,1) == std::numeric_limits<uint32_t>::max());

    //Test6: MAximum value overflow
    assert(alu.add(std::numeric_limits<uint32_t>::max(), 1) == 0);

    //Test7 : Bitwise AND
    assert(alu.bitwiseAnd(10, 12) == 8);

    //Test8 : Bitwise OR
    assert(alu.bitwiseOr(10, 12) == 14);

    //Test9 : Bitwise XOR
    assert(alu.bitwiseXor(10, 12) == 6);

    //Test 10 : AND with ZERO
    assert(alu.bitwiseAnd(42, 0) == 0);

    //Test 11 : OR with ZERO
    assert(alu.bitwiseOr(42, 0) == 42);

    //Test 12 : XOR with Same Values
    assert(alu.bitwiseXor(42, 42) == 0);

    //Test 13 : XOR with ZERO
    assert(alu.bitwiseXor(42, 0) == 42);
    std::cout<<"All ALU Test PASSED!\n";

    //Test 14 : Logical left shift
    assert(alu.shiftLeftLogical(5, 1) == 10);

    //Test 15 : Logical right shift
    assert(alu.shiftRightLogical(20, 2) == 5);

    //Test 16 : Arithmetic right shift of a negative value
    assert(alu.shiftRightArithmetic(0xFFFFFFF8, 1) == 0xFFFFFFFC);

    //Test 17 : Shift amount greater than 31 uses lower 5 bits
    assert(alu.shiftLeftLogical(5, 33) == 10);

    //Test 18 : Shifting by zero preserves the value
    assert(alu.shiftRightLogical(123, 0) == 123);

    return 0;
}
