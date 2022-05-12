//
// Created by mkuja on 11.5.2022.
//

#include <stdio.h>

#include "chunk.h"
#include "debug.h"

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, int offset, Chunk* chunk) {
    uint8_t constant = chunk->code[offset+1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("\n");
    return offset + 2;
}

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);
    if (offset > 0
            && getLine(&chunk->lines, offset) == getLine(&chunk->lines, offset - 1)) {
        printf("   | ");
    } else {
        printf("%4d ", getLine(&chunk->lines, offset));
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
            break;
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", offset, chunk);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
