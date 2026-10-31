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

    //-----------ADDI edge-case tests-----------
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


    
    //----------LUI instruction tests---------
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


    //----------AUIPC Test----------
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





    // ----------JAL TESTS----------
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




    // ----------JALR TESTS-----------
    // JALR Test1 : Positive immediate
    CPU jalr_positive_cpu;

    jalr_positive_cpu.setRegister(1, 100);

    // JALR x5, 20(x1)
    // rd = x5, rs1 = x1 immediate = 20

    jalr_positive_cpu.execute(0x014082E7);

    assert(jalr_positive_cpu.readRegister(5) == 4);
    assert(jalr_positive_cpu.getPC() == 120);


    //JALR Test2 : Negative immediate
    CPU jalr_negative_cpu;

    jalr_negative_cpu.setRegister(1, 100);

    //JALR x5, -20(x1)
    jalr_negative_cpu.execute(0xFEC082E7);

    assert(jalr_negative_cpu.readRegister(5) == 4);
    assert(jalr_negative_cpu.getPC() == 80);


    // JALR Test3 : Desitnation is x0
    CPU jalr_x0_cpu;
    jalr_x0_cpu.setRegister(1, 100);

    //JALR x0, 20(x1)
    jalr_x0_cpu.execute(0x01408067);

    assert(jalr_x0_cpu.readRegister(0) == 0);
    assert(jalr_x0_cpu.getPC() == 120);



    //------------BEQ Tests------------
    //BEQ Test1 : Branch taken (x1 == x2)
    CPU beq_taken_cpu;

    beq_taken_cpu.setRegister(1, 10);
    beq_taken_cpu.setRegister(2, 10);

    //BEQ x1, x2, +8
    beq_taken_cpu.execute(0x00208463);

    assert(beq_taken_cpu.getPC() == 8);

    //BEQ Test2 : Branch not taken (x1 != x2)
    CPU beq_not_taken_cpu;

    beq_not_taken_cpu.setRegister(1, 10);
    beq_not_taken_cpu.setRegister(2, 20);

    //BEQ x2, x2, +8   
    beq_not_taken_cpu.execute(0x00208463);
    
    assert(beq_not_taken_cpu.getPC() == 4);

    //BEQ Test3 : Negative branch offset
    CPU beq_negative_cpu;

    beq_negative_cpu.setRegister(1, 10);
    beq_negative_cpu.setRegister(2, 10);

    //Set PC to 16 by executing four NOPs
    beq_negative_cpu.loadProgram({
        0x00000013, //NOP
        0x00000013, //NOP
        0x00000013, //NOP
        0x00000013, //NOP
        0xFE208CE3  //BEQ x1, x2, -8
    });

    assert(beq_negative_cpu.step());
    assert(beq_negative_cpu.step());
    assert(beq_negative_cpu.step());
    assert(beq_negative_cpu.step());

    assert(beq_negative_cpu.getPC() == 16);

    assert(beq_negative_cpu.step());

    assert(beq_negative_cpu.getPC() == 8);




    //-----------BNE Tests--------------
    //BNE Test1 : Branch taken (x1 != x2)
    CPU bne_taken_cpu;

    bne_taken_cpu.setRegister(1, 10);
    bne_taken_cpu.setRegister(2, 20);

    //BNE x1, x2, +8
    bne_taken_cpu.execute(0x00209463);

    assert(bne_taken_cpu.getPC() == 8);


    //BNE Test2 : Branch not taken (x1 == x2)
    CPU bne_not_taken_cpu;

    bne_not_taken_cpu.setRegister(1, 10);
    bne_not_taken_cpu.setRegister(2, 10);

    //BNE x1, x2, +8
    bne_not_taken_cpu.execute(0x00209463);

    assert(bne_not_taken_cpu.getPC() == 4);


    //BNE Test3 : Negative branch offset
    CPU bne_negative_cpu;

    bne_negative_cpu.setRegister(1, 10);
    bne_negative_cpu.setRegister(2, 20);

    bne_negative_cpu.loadProgram({
        0x00000013, //NOP
        0x00000013, //NOP
        0x00000013, //NOP
        0x00000013, //NOP
        0xFE209CE3 //BNE x1, x2, -8
    });

    assert(bne_negative_cpu.step());
    assert(bne_negative_cpu.step());
    assert(bne_negative_cpu.step());
    assert(bne_negative_cpu.step());

    assert(bne_negative_cpu.getPC() == 16);

    assert(bne_negative_cpu.step());

    assert(bne_negative_cpu.getPC() == 8);


    //-----------BLT Tests--------------    
    //BLT Test1 : Branch taken (5 < 10)
    CPU blt_taken_cpu;
    blt_taken_cpu.setRegister(1, 5);
    blt_taken_cpu.setRegister(2, 10);
    blt_taken_cpu.execute(0x0020C463); //BLT x1, x2, +8
    assert(blt_taken_cpu.getPC() == 8);

    //BLT Test2 : Branch not taken (10 < 5 is false)
    CPU blt_not_taken_cpu;
    blt_not_taken_cpu.setRegister(1, 10);
    blt_not_taken_cpu.setRegister(2, 5);
    blt_not_taken_cpu.execute(0x0020C463); //BLT x1, x2, +8
    assert(blt_not_taken_cpu.getPC() == 4);

    //BLT Test3 : Negative signed value (-1 < 3)
    CPU blt_signed_cpu;
    blt_signed_cpu.setRegister(1, 0xFFFFFFFF);
    blt_signed_cpu.setRegister(2, 3);
    blt_signed_cpu.execute(0x0020C463); //BLT x1, x3, +8
    assert(blt_signed_cpu.getPC() == 8);


    //-----------BGE Tests--------------
    //BGE Test 1 : Branch taken (10 >= 5)
    CPU bge_taken_cpu;
    bge_taken_cpu.setRegister(1, 10);
    bge_taken_cpu.setRegister(2, 5);
    bge_taken_cpu.execute(0x0020D463); //BGE x1, x2, +8
    assert(bge_taken_cpu.getPC() == 8);

    //BGE Test 2 : Branch not taken (S > = 10 is false)
    CPU bge_not_taken_cpu;
    bge_not_taken_cpu.setRegister(1, 5);
    bge_not_taken_cpu.setRegister(2, 10);
    bge_not_taken_cpu.execute(0x0020D463);
    assert(bge_not_taken_cpu.getPC() == 4);

    //BGE Test 3 : Negative signed comparison (-1 >= 3 is false)
    CPU bge_signed_cpu;
    bge_signed_cpu.setRegister(1, 0xFFFFFFFF);
    bge_signed_cpu.setRegister(2, 3);
    bge_signed_cpu.execute(0x0020D463);
    assert(bge_signed_cpu.getPC() == 4);



    //-----------BLTU Tests--------------
    //BLTU Test 1 : Branch taken (2 < 3)
    CPU bltu_taken_cpu;
    bltu_taken_cpu.setRegister(1, 2);
    bltu_taken_cpu.setRegister(2, 3);
    bltu_taken_cpu.execute(0x0020E463); //BLTU x1, x2, +8
    assert(bltu_taken_cpu.getPC() == 8);

    //BLTU Test 2 : Branch not taken (3 < 2 is false)
    CPU bltu_not_taken_cpu;
    bltu_not_taken_cpu.setRegister(1, 3);
    bltu_not_taken_cpu.setRegister(2, 2);
    bltu_not_taken_cpu.execute(0x0020E463);
    assert(bltu_not_taken_cpu.getPC() == 4);

    //BLTU Test 3 : 0xFFFFFFFF is a large unsigned value
    CPU bltu_unsigned_cpu;
    bltu_unsigned_cpu.setRegister(1, 0xFFFFFFFF);
    bltu_unsigned_cpu.setRegister(2, 3);
    bltu_unsigned_cpu.execute(0x0020E463);
    assert(bltu_unsigned_cpu.getPC() == 4);



    //-----------BGEU Tests--------------
    //BGEU Test 1 : Branch taken (10 >= 5)
    CPU bgeu_taken_cpu;
    bgeu_taken_cpu.setRegister(1, 10);
    bgeu_taken_cpu.setRegister(2, 5);
    bgeu_taken_cpu.execute(0x0020F463); //BGEU x1, x2, +8
    assert(bgeu_taken_cpu.getPC() == 8) ;

    //BGEU Test 2 : branch not taken (5 >= 10 is false)
    CPU bgeu_not_taken_cpu;
    bgeu_not_taken_cpu.setRegister(1, 5);
    bgeu_not_taken_cpu.setRegister(2, 10);
    bgeu_not_taken_cpu.execute(0x0020F463);
    assert(bgeu_not_taken_cpu.getPC() == 4);

    //BGEU Test 3 : Large unsigned value >= 3
    CPU bgeu_unsigned_cpu;
    bgeu_unsigned_cpu.setRegister(1, 0xFFFFFFFF);
    bgeu_unsigned_cpu.setRegister(2, 3);
    bgeu_unsigned_cpu.execute(0x0020F463);
    assert(bgeu_unsigned_cpu.getPC() == 8);
    return 0;

}
