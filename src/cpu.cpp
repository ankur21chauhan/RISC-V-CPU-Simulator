#include "cpu.hpp"
#include<stdexcept>

CPU::CPU() : pc_(0) {}

void CPU::execute(uint32_t instruction){
    const uint32_t opcode = decoder_.opcode(instruction);

    //RISC-V R-type integer register-register instructions

    if(opcode != 0x33){
        throw std::invalid_argument("Unsupported instruction opcode");
    }

    const uint32_t destination = decoder_.rd(instruction);
    const uint32_t source1 = decoder_.rs1(instruction);
    const uint32_t source2 = decoder_.rs2(instruction);
    const uint32_t function3 = decoder_.funct3(instruction);
    const uint32_t function7 = decoder_.funct7(instruction);
    const uint32_t a = registers_.read(source1);
    const uint32_t b = registers_.read(source2);

    uint32_t result = 0;

    if(function3 == 0x0 && function7 == 0x00){
        //ADD
        result = alu_.add(a, b);
    }
    else if(function3 == 0x0 && function7 == 0x20){
        //SUB
        result = alu_.sub(a, b);
    }
    else{
        throw std::invalid_argument("Unsupported R-type instruction");
    }

    registers_.write(destination, result);

    //RV32I instructions are 32 bits (4 bytes) wide

    pc_ += 4;

}

uint32_t CPU::readRegister(uint32_t index) const{
    return registers_.read(index);
}

uint32_t CPU::getPC() const{
    return pc_;
}

void CPU::setRegister(uint32_t index, uint32_t value){
    registers_.write(index, value);
}