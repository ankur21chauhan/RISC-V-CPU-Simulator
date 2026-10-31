#include "decoder.hpp"

uint32_t Decoder::opcode(uint32_t instruction) const{
    return instruction & 0x7F;
}

uint32_t Decoder::rd(uint32_t instruction) const{
    return (instruction >> 7) & 0x1F;
}

uint32_t Decoder::funct3(uint32_t instruction) const{
    return (instruction >> 12) & 0x07;
}

uint32_t Decoder::rs1(uint32_t instruction) const{
    return (instruction >> 15) & 0x1F;
}

uint32_t Decoder::rs2(uint32_t instruction) const{
    return (instruction >> 20) & 0x1F;
}

uint32_t Decoder::funct7(uint32_t instruction) const{
    return (instruction >> 25) & 0x7F;
}

uint32_t Decoder::immediateI(uint32_t instruction) const{
    uint32_t immediate = (instruction >> 20) & 0xFFF;

    //if bit 11 is set, the 12-bit immediate is negative
    if((immediate & 0x800) != 0){
        immediate |= 0xFFFFF000;
    }

    return immediate;
}


uint32_t Decoder::immediateU(uint32_t instruction) const{
    return instruction & 0xFFFFF000; //0xFFFFF000 is a bitmask
}

//JAL immediate range −1,048,576 to +1,048,574 bytes
uint32_t Decoder::immediateJ(uint32_t instruction) const{
    uint32_t immediate = 0;

    immediate |= ((instruction >> 31) & 0x1) <<20;
    immediate |= ((instruction >> 21) & 0x3FF) << 1;
    immediate |= ((instruction >> 20) & 0x1) << 11;
    immediate |= ((instruction) >> 12 & 0xFF) << 12;

    //Sign-extend the 21-bit immediate
    if ((immediate & 0x100000) != 0){
        immediate |= 0xFFE00000;
    }

    return immediate;
}


uint32_t Decoder::immediateB(uint32_t instruction) const{
    uint32_t immediate = 0;

    //Extract and position the B-type immediate bits.
    immediate |= ((instruction >> 31) & 0x1) << 12;
    immediate |= ((instruction >> 25) & 0x3F) << 5;
    immediate |= ((instruction >> 8) & 0xF) << 1;
    immediate |= ((instruction >> 7) & 0x1) << 11;

    //Sign-extend the 13-bit immediate
    if((immediate & 0x1000) != 0){
        immediate |= 0xFFFFE000;
    }

    return immediate;
    
}