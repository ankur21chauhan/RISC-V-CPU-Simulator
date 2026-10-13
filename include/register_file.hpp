#ifndef REGISTER_FILE_HPP
#define REGISTER_FILE_HPP

#include<array>
#include<cstdint>

class RegisterFile{
public:
	RegisterFile();
	
	uint32_t read(uint32_t index) const;
	void write(uint32_t index, uint32_t value);

private:
	std::array<uint32_t, 32 > registers_;

};


#endif
