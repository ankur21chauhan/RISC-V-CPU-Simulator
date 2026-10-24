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