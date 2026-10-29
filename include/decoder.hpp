#ifndef DECODER_HPP
#define DECODER_HPP

#include<cstdint>
class Decoder{
public:
    uint32_t opcode(uint32_t instruction) const;
    uint32_t rd(uint32_t instruction) const;
    uint32_t funct3(uint32_t instruction) const;
    uint32_t rs1(uint32_t instruction) const;
    uint32_t rs2(uint32_t instruction) const;
    uint32_t funct7(uint32_t instruction) const;
    uint32_t immediateI(uint32_t instruction) const;
    uint32_t immediateU(uint32_t instruction) const;

};

#endif