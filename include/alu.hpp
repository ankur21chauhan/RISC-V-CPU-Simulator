//Header Guards
#ifndef ALU_HPP
#define ALU_HPP

#include<cstdint> //for fixed width integer types

class ALU{
    public:
        uint32_t add(uint32_t a, uint32_t b) const; 
        uint32_t sub(uint32_t a, uint32_t b) const;
        //const after? so that member function cannot modify the state of ALU object
};

#endif