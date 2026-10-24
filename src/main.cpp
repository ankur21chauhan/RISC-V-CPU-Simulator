#include<cstdint>
#include<vector>
#include<iostream>

#include"cpu.hpp"

using namespace std;


int main(){
	CPU cpu;

	//set initial register values
	cpu.setRegister(10, 15);
	cpu.setRegister(11, 20);

	/*
	Three Machine instructions:
	ADD x12, x10, x11 -> x12 = 15+20 = 35
	SUB x13, x12, x10 -> x13 = 35 - 15 = 20
	ADD x14, x13, x11 -> x14 = 20 + 20 = 40 */
	const std::vector<uint32_t> program = {
		0x00B50633,
		0x40A606B3,
		0x00B68733
	};

	cpu.loadProgram(program);

	cout<<"RISC-V CPU SIMULATOR\n";
	cout<<"--------------------\n";
	cout<<"Starting Program Execution!\n";

	size_t instruction_number = 1;

	while(true){
		const uint32_t pc_before = cpu.getPC();
		if(!cpu.step()){
			break;
		}

		cout<<"\nInstruction" <<instruction_number++ <<"\n";
		cout<<"PC before : "<<pc_before <<'\n';
		cout<<"PC after : "<<cpu.getPC() << '\n';
	}

	cout << "\nFinal register state:\n";
    cout << "x10 = " << cpu.readRegister(10) << '\n';
    cout << "x11 = " << cpu.readRegister(11) << '\n';
	cout << "x12 = " << cpu.readRegister(12) << '\n';
	cout << "x13 = " << cpu.readRegister(13) << '\n';
	cout << "x14 = " << cpu.readRegister(14) << '\n';
    cout << "PC   = " << cpu.getPC() << '\n';

    cout << "\nProgram execution completed!\n";

	return 0;


}