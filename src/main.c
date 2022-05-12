#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    writeChunk(&chunk, OP_RETURN, 1);
    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);

    writeChunk(&chunk, OP_RETURN, 3);
    writeChunk(&chunk, OP_RETURN, 4);
    writeChunk(&chunk, OP_RETURN, 5);

    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}
