#ifndef DATA_MEMORY_HPP
#define DATA_MEMORY_HPP

#include<cstdint>
#include<vector>

class DataMemory{
public:
    explicit DataMemory(uint32_t size);

    uint8_t loadByte(uint32_t address) const; //1 byte read
    uint16_t loadHalfWord(uint32_t address) const; //2 bytes read
    uint32_t loadWord(uint32_t address) const; //4 bytes read

    void storeWord(uint32_t address, uint32_t value);

    uint32_t size() const; //will return total size of the memory

private:
    std::vector<uint8_t> memory_;

    void checkAddress(uint32_t address, uint32_t bytes) const;

};


#endif

