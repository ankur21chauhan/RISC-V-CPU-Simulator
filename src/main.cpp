#include<iostream>
#include"cpu.hpp"
using namespace std;
int main(){
	CPU cpu;

	//set initial register values
	cpu.setRegister(10, 15);
	cpu.setRegister(11, 20);

	//machine code for: ADD x10, x10, x11
	const uint32_t instruction = 0x00B50533;

	cout<<"RISC-V CPU SIMULATOR\n";
	cout<<"--------------------\n";

	cout << "Instruction: ADD x10, x10, x11\n";
    cout << "Before execution:\n";
    cout << "x10 = " << cpu.readRegister(10) << '\n';
    cout << "x11 = " << cpu.readRegister(11) << '\n';
    cout << "PC   = " << cpu.getPC() << '\n';

	cpu.execute(instruction);

	cout << "\nAfter execution:\n";
    cout << "x10 = " << cpu.readRegister(10) << '\n';
    cout << "x11 = " << cpu.readRegister(11) << '\n';
    cout << "PC   = " << cpu.getPC() << '\n';

    cout << "\nInstruction executed successfully!\n";

	return 0;


}