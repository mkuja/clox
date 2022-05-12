//
// Created by mkuja on 12.5.2022.
//

#include "uint24_t.h"


uint32_t convertBack(uint24_t num) {
    uint32_t returnValue = 0;
    returnValue |= num.a;
    returnValue <<= 8;
    returnValue |= num.b;
    returnValue <<= 8;
    returnValue |= num.c;
    return returnValue;
}

uint24_t convertTo(uint32_t num) {
    uint24_t returnValue;
    returnValue.c = (num & 0xFF);
    returnValue.b = ((num >> 8) & 0xFF);
    returnValue.a = ((num >> 16) & 0xFF);
    return returnValue;
}
