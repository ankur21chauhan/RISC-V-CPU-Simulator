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

    //ADDI edge-case tests
    CPU edge_cpu;

    //Test 1: immediate ZERO
    edge_cpu.setRegister(5, 100);
    edge_cpu.execute(0x00028293); // ADDI x5, x5, 0
    assert(edge_cpu.readRegister(5) == 100);

    //Test 2: Negative immediate (-1)
    edge_cpu.setRegister(6, 10);
    edge_cpu.execute(0xFFF30313); // ADDI x6, x6, -1
    assert(edge_cpu.readRegister(6) == 9);

    //Test 3: Maximum positice immediate (2047)
    edge_cpu.setRegister(7, 0);
    edge_cpu.execute(0x7FF38393); // ADDI x7, x7, 2047
    assert(edge_cpu.readRegister(7) == 2047);


    //Test 4: Minimum negative immediate (-2048)
    edge_cpu.setRegister(8, 0);
    edge_cpu.execute(0x80040413); // ADDI x8, x8, -2048
    assert(edge_cpu.readRegister(8) == 0xFFFFF800u);

    //Test 5: Destination 0x must remain ZERO
    edge_cpu.execute(0x00100013); // ADDI x0, x0, 1
    assert(edge_cpu.readRegister(0) == 0);

    //LUI instruction tests
    CPU lui_cpu;

    //Test1: Load upper immediate
    lui_cpu.execute(0x123452B7); //LUI x5, 0x12345
    assert(lui_cpu.readRegister(5) == 0x12345000);

    //Test2: upper immediate with all 20 bits set
    lui_cpu.execute(0xFFFFF337); //LUI x6, 0xFFFFF
    assert(lui_cpu.readRegister(6) == 0xFFFFF000u);

    //Test3 : 0x must remain ZERO
    lui_cpu.execute(0x12345037); //LUI 0x, 0x12345
    assert(lui_cpu.readRegister(0) == 0);


    //AUIPC Test
    CPU auipc_cpu;

    //PC starts at 0
    auipc_cpu.execute(0x12345297); //AUIPC x5, 0x12345

    assert(auipc_cpu.readRegister(5) == 0x12345000);
    assert(auipc_cpu.getPC() == 4);


    CPU auipc_pc_cpu;

    auipc_pc_cpu.loadProgram({
        0x00000013, //ADDI 0x, x0, 0 (NOP)
        0x12345297 //AUIPC x5, 0x12345
    });

    assert(auipc_pc_cpu.step());
    assert(auipc_pc_cpu.getPC() == 4);

    assert(auipc_pc_cpu.step());
    assert(auipc_pc_cpu.readRegister(5) == 0x12345004);
    assert(auipc_pc_cpu.getPC() == 8);





    // JAL TESTS
    //JAL TEST1 : Positive jump offset
    CPU jal_cpu;

    jal_cpu.execute(0x008002EF);  // JAL x5, 8
    
    assert(jal_cpu.readRegister(5) == 4);
    assert(jal_cpu.getPC() == 8);

    //JAL TEST2 : Negative jump offset
    CPU jal_negaive_cpu;
    
    jal_negaive_cpu.loadProgram({
        0x00000013, //NOP
        0x00000013, //NOP
        0x00000013, //NOP
        0x00000013, //NOP
        0XFF9FF2EF //JAL x5, -8
    });

    //Execute four NOPs; PC advances from 0 to 16.
    assert(jal_negaive_cpu.step());
    assert(jal_negaive_cpu.step());
    assert(jal_negaive_cpu.step());
    assert(jal_negaive_cpu.step());

    assert(jal_negaive_cpu.getPC() == 16);

    //Execute JAL x5, -8
    assert(jal_negaive_cpu.step());

    assert(jal_negaive_cpu.readRegister(5) == 20);
    assert(jal_negaive_cpu.getPC() == 8);


    //JAL Test3 : Destination is x0
    CPU jal_x0_cpu;

    jal_x0_cpu.execute(0x0080006F); //JAL x0, 8
    assert(jal_x0_cpu.readRegister(0) == 0);
    assert(jal_x0_cpu.getPC() == 8);

    return 0;

}
