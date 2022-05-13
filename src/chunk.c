//
// Created by mkuja on 11.5.2022.
//

#include <stdlib.h>
#include "chunk.h"
#include "memory.h"
#include "uint24_t.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initLineRle(&chunk->lines);
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);

        int linesOldCapacity = chunk->lines.capacity;
        int linesNewCapacity = GROW_CAPACITY(linesOldCapacity);
        chunk->lines.lines = GROW_ARRAY(
                LineMeta, chunk->lines.lines, linesOldCapacity, linesNewCapacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
    incrementLineRle(&chunk->lines, line);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines.lines, chunk->lines.capacity);
    initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, Value value, int line) {
    uint32_t nthConstant = addConstant(chunk, value);
    if (nthConstant < 256) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, (char) nthConstant, line);
    }
    else {
        uint24_t constOrdinal = convertTo(nthConstant);
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, constOrdinal.a, line);
        writeChunk(chunk, constOrdinal.b, line);
        writeChunk(chunk, constOrdinal.c, line);
    }
}