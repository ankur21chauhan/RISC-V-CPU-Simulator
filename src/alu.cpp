#include "alu.hpp"

uint32_t ALU::add(uint32_t a, uint32_t b) const{
    return a+b;
}

uint32_t ALU::sub(uint32_t a, uint32_t b) const{
    return a-b;
}

uint32_t ALU::bitwiseAnd(uint32_t a, uint32_t b) const{
    return a & b;
}

uint32_t ALU::bitwiseOr(uint32_t a, uint32_t b) const{
    return a | b;
}

uint32_t ALU::bitwiseXor(uint32_t a, uint32_t b) const{
    return a ^ b;
}

uint32_t ALU::shiftLeftLogical(uint32_t value, uint32_t amount) const{
    return value << (amount & 0x1F);
}

uint32_t ALU::shiftRightLogical(uint32_t value, uint32_t amount) const{
    return value >> (amount & 0x1F);
}

uint32_t ALU::shiftRightArithmetic(uint32_t value, uint32_t amount) const{
    const int32_t signed_value = static_cast<int32_t>(value);
    return static_cast<uint32_t>(signed_value >> (amount & 0x1F));
}