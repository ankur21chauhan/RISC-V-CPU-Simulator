//Header Guards
#ifndef ALU_HPP
#define ALU_HPP

#include<cstdint> //for fixed width integer types

class ALU{
    public:
        uint32_t add(uint32_t a, uint32_t b) const; 
        uint32_t sub(uint32_t a, uint32_t b) const;
        //const after? so that member function cannot modify the state of ALU object

        uint32_t bitwiseAnd(uint32_t a, uint32_t b) const;
        uint32_t bitwiseOr(uint32_t a, uint32_t b) const;
        uint32_t bitwiseXor(uint32_t a, uint32_t b) const;
        uint32_t shiftLeftLogical(uint32_t value, uint32_t amount) const;
        uint32_t shiftRightLogical(uint32_t value, uint32_t amount) const;
        uint32_t shiftRightArithmetic(uint32_t value, uint32_t amount) const;


};

#endif