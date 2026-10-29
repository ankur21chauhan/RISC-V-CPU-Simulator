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

    else if(opcode == 0x37){ //0x37 LUI opcode
        const uint32_t destination = decoder_.rd(instruction);
        const uint32_t result = decoder_.immediateU(instruction);

        registers_.write(destination, result);
    }

    else {
        throw std::invalid_argument("Unsupported instruction opcode");
    }

    // Advance PC only after successful instruction execution.
    // Each supported RV32I instruction is 4 bytes wide.
    pc_ += 4;
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