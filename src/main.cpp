#include <cstdint>
#include <vector>
#include <iostream>

#include "cpu.hpp"

using namespace std;

int main() {
    CPU cpu;

    /*
        Three machine instructions:
        ADDI x5, x0, 10  -> x5 = 0 + 10 = 10
        ADDI x6, x5, 20  -> x6 = 10 + 20 = 30
        ADD  x7, x5, x6  -> x7 = 10 + 30 = 40
    */
    const vector<uint32_t> program = {
        0x00A00293, //ADDI x5, x0, 10
        0x01428313, //AADI x6, x5, 20
        0x006283B3, // AADI x7, x5, x5
        0x123453B7 // LUI x7, 0x12345
    };

    cpu.loadProgram(program);

    cout << "RISC-V CPU SIMULATOR\n";
    cout << "--------------------\n";
    cout << "Starting Program Execution!\n";

    size_t instruction_number = 1;

    while (true) {
        const uint32_t pc_before = cpu.getPC();

        if (!cpu.step()) {
            break;
        }

        cout << "\nInstruction " << instruction_number++ << "\n";
        cout << "PC before : " << pc_before << '\n';
        cout << "PC after  : " << cpu.getPC() << '\n';
    }

    cout << "\nFinal register state:\n";
    cout << "x5  = " << cpu.readRegister(5) << '\n';
    cout << "x6  = " << cpu.readRegister(6) << '\n';
    cout << "x7  = " << cpu.readRegister(7) << '\n';
    cout << "PC  = " << cpu.getPC() << '\n';

    cout << "\nProgram execution completed!\n";

    return 0;
}