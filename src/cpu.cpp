#include "cpu.hpp"
#include <stdexcept>

CPU::CPU() : pc_(0) {}

void CPU::loadProgram(const std::vector<uint32_t>& program) {
    instruction_memory_ = program;
    pc_ = 0;
}

bool CPU::step() {
    if (pc_ % 4 != 0) {
        throw std::runtime_error("PC is not instruction-aligned");
    }

    const std::size_t instruction_index = pc_ / 4;

    if (instruction_index >= instruction_memory_.size()) {
        return false;
    }

    const uint32_t instruction = instruction_memory_[instruction_index];

    execute(instruction);

    return true;
}

void CPU::execute(uint32_t instruction) {
    const uint32_t opcode = decoder_.opcode(instruction);
    bool advance_pc = true;

    // R-type instructions: ADD and SUB
    if (opcode == 0x33) {
        const uint32_t destination = decoder_.rd(instruction);
        const uint32_t source1 = decoder_.rs1(instruction);
        const uint32_t source2 = decoder_.rs2(instruction);

        const uint32_t function3 = decoder_.funct3(instruction);
        const uint32_t function7 = decoder_.funct7(instruction);

        const uint32_t a = registers_.read(source1);
        const uint32_t b = registers_.read(source2);

        uint32_t result = 0;

        if (function3 == 0x0 && function7 == 0x00) {
            // ADD: rd = rs1 + rs2
            result = alu_.add(a, b);
        }
        else if (function3 == 0x0 && function7 == 0x20) {
            // SUB: rd = rs1 - rs2
            result = alu_.sub(a, b);
        }
        else {
            throw std::invalid_argument("Unsupported R-type instruction");
        }

        registers_.write(destination, result);
    }

    // I-type instruction: ADDI
    else if (opcode == 0x13) {
        const uint32_t destination = decoder_.rd(instruction);
        const uint32_t source1 = decoder_.rs1(instruction);
        const uint32_t function3 = decoder_.funct3(instruction);

        const uint32_t a = registers_.read(source1);

        uint32_t result = 0;

        if (function3 == 0x0) {
            // ADDI: rd = rs1 + sign-extended immediate
            const uint32_t immediate = decoder_.immediateI(instruction);

            result = alu_.add(a, immediate);
        }
        else {
            throw std::invalid_argument("Unsupported I-type instruction");
        }

        registers_.write(destination, result);
    }
    
    // LUI BLOCK
    else if(opcode == 0x37){ //0x37 LUI opcode
        const uint32_t destination = decoder_.rd(instruction);
        const uint32_t result = decoder_.immediateU(instruction);

        registers_.write(destination, result);
    }

    // AUIPC BLOCK
    else if(opcode == 0x17){
        const uint32_t destination = decoder_.rd(instruction);
        const uint32_t immediate = decoder_.immediateU(instruction);

        const uint32_t result = pc_ + immediate;
        registers_.write(destination, result);
    }


    // JAL BLOCK
    else if(opcode == 0x6F){
        //JAL: rd = PC + 4; PC = PC + immediate

        const uint32_t destination = decoder_.rd(instruction);
        const uint32_t immediate = decoder_.immediateJ(instruction);

        const uint32_t old_pc = pc_;
        const uint32_t return_address = old_pc + 4;
        const uint32_t target_pc = old_pc + immediate;

        registers_.write(destination, return_address);
        pc_ = target_pc;

        //JAL has already updated the PC
        advance_pc = false;
    }

    // JALR BLOCK
    else if(opcode == 0x67){
        if(decoder_.funct3(instruction) != 0){
            throw std::invalid_argument("Invalid JALR funct3");
        }
        
        //JALR: rd = PC + 4; PC = (rs1 + immediate) & -1

        const uint32_t destination = decoder_.rd(instruction);
        const uint32_t source = decoder_.rs1(instruction);
        const uint32_t immediate = decoder_.immediateI(instruction);

        const uint32_t old_pc = pc_;
        const uint32_t source_value = registers_.read(source);

        const uint32_t return_address =  old_pc + 4;
        const uint32_t target_pc = (source_value + immediate) & -uint32_t{1};

        registers_.write(destination, return_address);
        pc_ = target_pc;

        //JALR has already updated the PC.
        advance_pc = false;

    }

    else if(opcode == 0x63){
        //BEQ: if (rs1 == rs2), PC = PC + immediate

        const uint32_t source1 = decoder_.rs1(instruction);
        const uint32_t source2 = decoder_.rs2(instruction);
        const uint32_t funct3 = decoder_.funct3(instruction);

        if(funct3 == 0x0){
            const uint32_t value1 = registers_.read(source1);
            const uint32_t value2  = registers_.read(source2);
            const uint32_t immediate = decoder_.immediateB(instruction);

            if(value1 == value2){
                pc_ += immediate;
                advance_pc = false;
            }
        }
        else{
            throw std::invalid_argument("Unsupported branch instruction");
        }
    }


    else {
        throw std::invalid_argument("Unsupported instruction opcode");
    }

    // Advance PC only after successful instruction execution.
    
    if(advance_pc){
        pc_ += 4;
    }
}

uint32_t CPU::readRegister(uint32_t index) const {
    return registers_.read(index);
}

uint32_t CPU::getPC() const {
    return pc_;
}

void CPU::setRegister(uint32_t index, uint32_t value) {
    registers_.write(index, value);
}