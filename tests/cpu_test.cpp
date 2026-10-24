#include "cpu.hpp"

#include<cassert>
#include<cstdint>
#include<iostream>
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

    return 0;

}