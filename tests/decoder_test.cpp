#include "decoder.hpp"

#include<cassert>
#include<cstdint>
#include<iostream>

int main(){
    Decoder decoder;
    const uint32_t instruction = 0x00B50533;

    assert(decoder.opcode(instruction) == 0x33);
    assert(decoder.rd(instruction) == 10);
    assert(decoder.funct3(instruction) == 0);
    assert(decoder.rs1(instruction) == 10);
    assert(decoder.rs2(instruction) == 11);
    assert(decoder.funct7(instruction) == 0);

    std::cout<<"All Decoder test passed!\n";

    //ADDI x5, x0, 10
    assert(decoder.immediateI(0x00A00293) == 10);

    //ADDI x6, x0, -1
    assert(decoder.immediateI(0xFFF00313) == 0xFFFFFFFFu);

    assert(decoder.immediateU(0x12345287) == 0x12345000);


    //B-Type immediate tests


    //TEST1 : Positive immediate (+8)
    //BEQ x0, x0, +8
    assert(decoder.immediateB(0x00000463) == 8);

    //TEST2 : Negative immediate (-8)
    //BEQ x0, x0, -8
    assert(decoder.immediateB(0xFE000CE3) == 0xFFFFFFF8);

    //TEST3 : Zero immediate
    //BEQ x0, x0, 0
    assert(decoder.immediateB(0x00000063) == 0);

    return 0;
}