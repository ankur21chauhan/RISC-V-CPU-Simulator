#include "register_file.hpp"
#include<stdexcept>

RegisterFile::RegisterFile()
	: registers_{} {
}

uint32_t RegisterFile::read(uint32_t index) const{
	if(index >= registers_.size()){
		throw std::out_of_range("Invalid register index");
	}
	
	return registers_[index];
}

void RegisterFile::write(uint32_t index, uint32_t value) {
	if(index >= registers_.size()){
		throw std::out_of_range("Invalid register index");
	}

	if(index == 0){
		return;
	}

	registers_[index] = value;

}
