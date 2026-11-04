#include "data_memory.hpp"
#include <stdexcept>

//Constructor: initialize memory with the requested size
//All bytes are initialized to ZERO
DataMemory::DataMemory(uint32_t size)
    : memory_(size, 0) {}

//Check whether the requested memory range is valid
void DataMemory::checkAddress(uint32_t address, uint32_t bytes) const {
    if (address > memory_.size() || bytes > memory_.size() - address){
        throw std::out_of_range("Data memory access out of bounds");
    }
}

//Load one byte
uint8_t DataMemory::loadByte(uint32_t address) const{
    checkAddress(address, 1);
    return memory_[address];
}

//Load two bytes using little-endian byte order
uint16_t DataMemory::loadHalfWord(uint32_t address) const{
    checkAddress(address, 2);
    
    uint16_t value = 0;
    value |= static_cast<uint16_t>(memory_[address]);
    value |= static_cast<uint16_t>(memory_[address + 1]) << 8;

    return value;
}

//Load four bytes using little-endian byte order
uint32_t DataMemory::loadWord(uint32_t address) const{
    checkAddress(address, 4);

    uint32_t value = 0;

    value |= static_cast<uint32_t>(memory_[address]);
    value |= static_cast<uint32_t>(memory_[address + 1]) << 8;
    value |= static_cast<uint32_t>(memory_[address + 2]) << 16;
    value |= static_cast<uint32_t>(memory_[address + 3]) << 24;

    return value;
}

//Store one byte
void DataMemory::storeByte(uint32_t address, uint8_t value){
    checkAddress(address, 1);
    memory_[address] = value;
}

//Store two bytes using little-endian byte order
void DataMemory::storeHalfWord(uint32_t address, uint16_t value){
    checkAddress(address, 2);

    memory_[address] = static_cast<uint8_t>(value & 0xFF);
    memory_[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

//Store four bytes using little-endian byte order
void DataMemory::storeWord(uint32_t address, uint32_t value){
    checkAddress(address, 4);

    memory_[address] = static_cast<uint8_t>(value & 0xFF);
    memory_[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    memory_[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    memory_[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);

}

//Return the total memory size in bytes
uint32_t DataMemory::size() const{
    return static_cast<uint32_t>(memory_.size());
}