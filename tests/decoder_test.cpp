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

    return 0;
}