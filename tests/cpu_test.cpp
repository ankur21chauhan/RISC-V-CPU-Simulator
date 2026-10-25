#include "cpu.hpp"

#include<cassert>
#include<cstdint>
#include<iostream>
#include<vector>
#include<stdexcept>

int main(){
    CPU cpu;

    //ADD x10, x10, x11
    const uint32_t addInstruction = 0x00B50533;

    cpu.setRegister(10, 15);
    cpu.setRegister(11, 20);

    cpu.execute(addInstruction);

    assert(cpu.readRegister(10) == 35);
    assert(cpu.readRegister(11) == 20);
    assert(cpu.getPC() == 4);

    //SUB x12, x10, x11a
    const uint32_t subInstruction = 0x40B50633;

    cpu.execute(subInstruction);

    assert(cpu.readRegister(12) == 15);
    assert(cpu.getPC() == 8);

    //x0 must remain ZERO
    cpu.setRegister(0, 100);
    assert(cpu.readRegister(0) == 0);

    //Unsupported opcode must be rejected
    bool threw = false;

    try{
        cpu.execute(0x00000000);
    }
    catch(const std::invalid_argument&){
        threw = true;
    }

    assert(threw);
    assert(cpu.getPC() == 8);

    std::cout<<"All CPU tests passed!\n";

    //Test PC-based instruction fetching
    CPU program_cpu;

    program_cpu.setRegister(10,15);
    program_cpu.setRegister(11, 20);


    const std::vector<uint32_t> program = {
        0x00B50633, //ADD x12, x10, x11
        0x40A606B3 //SUB x13, x12, x10
    };

    program_cpu.loadProgram(program);
    assert(program_cpu.getPC() == 0);

    //first fetched instruction
    assert(program_cpu.step());
    assert(program_cpu.readRegister(12) == 35);
    assert(program_cpu.getPC() == 4);

    //Second fetched instruction
    assert(program_cpu.step());
    assert(program_cpu.readRegister(13) == 20);
    assert(program_cpu.getPC() == 8);

    //No more instruction remain
    assert(!program_cpu.step());
    assert(program_cpu.getPC() == 8);


    CPU addi_cpu;
    addi_cpu.loadProgram({
        0x00A00293,
        0x01428313,
        0xFFF30393
    });

    assert(addi_cpu.step());
    assert(addi_cpu.readRegister(5) == 10);
    assert(addi_cpu.getPC() == 4);

    assert(addi_cpu.step());
    assert(addi_cpu.readRegister(6) == 30);
    assert(addi_cpu.getPC() == 8);

    assert(addi_cpu.step());
    assert(addi_cpu.readRegister(7) == 29);
    assert(addi_cpu.getPC() == 12);

    assert(!addi_cpu.step());
    assert(addi_cpu.getPC() == 12);




    return 0;

}
