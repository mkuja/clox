#include <stdio.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "uint24_t.h"
#include "vm.h"

int main(int argc, char *argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    initVM();

//    writeConstant(&chunk, 3.0, 1);
//    writeConstant(&chunk, 2.0, 1);
//    writeChunk(&chunk, OP_MULTIPLY, 1);
//    writeConstant(&chunk, 1.0, 1);
//    writeChunk(&chunk, OP_ADD, 1);
//    writeConstant(&chunk, 4.0, 1);
//    writeChunk(&chunk, OP_SUBTRACT, 1);
//    writeConstant(&chunk, 5.0, 1);
//    writeChunk(&chunk, OP_NEGATE, 1);
//    writeChunk(&chunk, OP_DIVIDE, 1);
//    writeChunk(&chunk, OP_RETURN, 1);

    writeConstant(&chunk, 2.0, 1);
    writeConstant(&chunk, 3.0, 1);
    writeConstant(&chunk, 1.0, 1);
    writeChunk(&chunk, OP_SUBTRACT, 1);
    writeChunk(&chunk, OP_SUBTRACT, 1);
    writeChunk(&chunk, OP_RETURN, 1);

    interpret(&chunk);
    freeChunk(&chunk);

//    uint24_t test = convertTo(123456U);
//    printf("sizeof: %d, value: %d\n", sizeof(test), convertBack(test));

    return 0;
}
