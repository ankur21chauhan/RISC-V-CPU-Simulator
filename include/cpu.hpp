#ifndef CPU_HPP
#define CPU_HPP

#include<cstdint>

#include "register_file.hpp"
#include "alu.hpp"
#include "decoder.hpp"

class CPU{
    public:
        CPU();
        void execute(uint32_t instruction); //will decode and execute the instruction

        uint32_t readRegister(uint32_t index) const;
        uint32_t getPC() const;

        void setRegister(uint32_t index, uint32_t value);

    private:
        RegisterFile registers_; //32 integer register of CPU
        ALU alu_; //arithmetic operations
        Decoder decoder_; //will extract fields of machine instructions

        uint32_t pc_;  //Program Counter

};

#endif