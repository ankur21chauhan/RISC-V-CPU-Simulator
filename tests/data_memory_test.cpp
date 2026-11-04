#include "data_memory.hpp"
#include<cassert>
#include<iostream>
#include<stdexcept>

int main(){
    //Test 1 : Memory initialization
    DataMemory memory(16);
    for(uint32_t address = 0; address < memory.size(); ++address){
        assert(memory.loadByte(address) == 0);
    }

    std::cout<<"Test 1 passed: Memory initializes to zero. \n";

    //Test 2: Store and load one byte 
    memory.storeByte(0, 0xAB);
    assert(memory.loadByte(0) == 0xAB);

    std::cout<<"Test 2 passed: Byte store/load worlds. \n";

    //Test 3 : Store and load half-word
    memory.storeHalfWord(2, 0x1234);

    assert(memory.loadHalfWord(2) == 0x1234);

    assert(memory.loadByte(2) == 0x34);
    assert(memory.loadByte(3) == 0x12);

    std::cout<<"Test 3 passed: Half-word store/load works. \n";

    //Test 4 : Store and load word
    memory.storeWord(4, 0x12345678);

    assert(memory.loadWord(4) == 0x12345678);

    assert(memory.loadByte(4) == 0x78);
    assert(memory.loadByte(5) == 0x56);
    assert(memory.loadByte(6) == 0x34);
    assert(memory.loadByte(7) == 0x12);

    std::cout<<"Test 4 passed: Word store/load works.\n";


    //Test 5 : Last valid byte address
    memory.storeByte(15, 0xAB);
    assert(memory.loadByte(15) == 0xAB);

    std::cout<<"Test 5 passed: last valid byte access works. \n";

    //Test 6 : Out-of-bounds read
    bool read_exception = false;

    try{
        memory.loadByte(16);
    }
    catch(const std::out_of_range&){
        read_exception = true;
    }

    assert(read_exception);

    std::cout<<"Test 6 passed: Out-of-bounds read is rejected.\n";


    //Test 7 : Out-of-bounds write
    bool write_exception = false;

    try{
        memory.storeByte(16, 0xFF);
    }
    catch(const std::out_of_range&){
        write_exception = true;
    }

    assert(write_exception);

    std::cout<<"Test 7 passed: Out-of-bounds write is rejected./n";

    //Test 8: Cross-boundary word access
    bool word_exception = false;

    try{
        memory.loadWord(13);
    }
    catch(const std::out_of_range&){
        word_exception = true;
    }

    assert(word_exception);

    std::cout<<"Test 8 passed: Cross-boundary word access is rejected.\n";

    return 0;


}
