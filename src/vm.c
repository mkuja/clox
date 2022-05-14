//
// Created by mkuja on 12.5.2022.
//

#include <stdio.h>
#include "debug.h"
#include "common.h"
#include "memory.h"
#include "compiler.h"
#include "vm.h"

VM vm;

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
do {                  \
    double b = pop(); \
    double a = pop(); \
    push(a op b);     \
} while (false)

    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("          ");
        for (Value *slot = vm.stack.data; slot < vm.stack.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(vm.chunk, (int) (vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_RETURN:
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
                case OP_NEGATE:
                    push(-pop());
                break;
                case OP_ADD:
                    BINARY_OP(+);
                break;
                case OP_SUBTRACT:
                    BINARY_OP(-);
                break;
                case OP_MULTIPLY:
                    BINARY_OP(*);
                break;
                case OP_DIVIDE:
                    BINARY_OP(/);
                break;
            }

        }
    }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

static void resetStack() {
    vm.stack.stackTop = vm.stack.data;
}

static void initStack() {
    int capacity = STACK_INITIAL;
    vm.stack.data = GROW_ARRAY(Value, vm.stack.data, 0, capacity);
}

static void resizeStack() {
    if (vm.stack.stackTop >= vm.stack.data + vm.stack.capacity) {
        int oldCapacity = vm.stack.capacity;
        int newCapacity = GROW_CAPACITY(oldCapacity);
        vm.stack.data = GROW_ARRAY(Value, vm.stack.data, oldCapacity, newCapacity);
    }
}

static void freeStack() {
    int stackCapacity = vm.stack.capacity;
    FREE_ARRAY(Value, vm.stack.data, stackCapacity);
}

void initVM() {
    initStack();
    resetStack();
}

void freeVM() {
    freeStack();
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}

void push(Value value) {
    resizeStack();
    *vm.stack.stackTop = value;
    vm.stack.stackTop++;
}

Value pop() {
    vm.stack.stackTop--;
    return *vm.stack.stackTop;
}
