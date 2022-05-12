#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "uint24_t.h"

int main(int argc, char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    writeChunk(&chunk, OP_RETURN, 1);

    writeConstant(&chunk, 5.0, 10);
    writeConstant(&chunk, 5.0, 10);


    writeChunk(&chunk, OP_RETURN, 3);
    writeChunk(&chunk, OP_RETURN, 4);
    writeChunk(&chunk, OP_RETURN, 5);

    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    uint24_t test = convertTo(123456U);
    printf("sizeof: %d, value: %d\n", sizeof(test), convertBack(test));

    return 0;
}
