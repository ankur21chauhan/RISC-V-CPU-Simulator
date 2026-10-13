#include "register_file.hpp"

#include<cassert>
#include<iostream>
#include<stdexcept>

int main(){
	RegisterFile rf;
	
	//Test 1: Registers start at ZERO
	assert(rf.read(0) == 0);
	assert(rf.read(1) == 0);
	assert(rf.read(2) == 0);

	//Test 2: Write and Read
	rf.write(5, 42);
	assert(rf.read(5) == 42);

	//Test 3: x0 must always remain ZERO
	rf.write(0, 100);
	assert(rf.read(0) == 0);

	//Test 4: Invalid index must throw
	bool exception_thrown = false;

	try{
		rf.read(32);
	}
	catch (const std::out_of_range&) {
		exception_thrown = true;
	}

	assert(exception_thrown);

	std::cout<<"All Register File test passed!\n";

	return 0;


};
