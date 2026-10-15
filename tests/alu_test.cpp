#include "alu.hpp"

#include<cassert>
#include<iostream>

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
    assert(alu.sub(0,1) == 4294967295U);

    std::cout<<"All ALU Test PASSED!\n";

    return 0;
}