//
// Created by mkuja on 12.5.2022.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "value.h"

#define STACK_INITIAL 256

typedef struct {
    Value* data;
    Value* stackTop;
    int capacity;
} Stack;

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    Stack stack;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();


#endif //CLOX_VM_H
