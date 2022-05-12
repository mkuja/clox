//
// Created by mkuja on 12.5.2022.
//

#ifndef CLOX_UINT24_T_H
#define CLOX_UINT24_T_H

#include <stdint.h>

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
} uint24_t;

uint32_t convertBack(uint24_t num);
uint24_t convertTo(uint32_t num);


#endif //CLOX_UINT24_T_H
