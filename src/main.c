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

    writeConstant(&chunk, 5.0, 1);
    writeChunk(&chunk, OP_RETURN, 2);

    interpret(&chunk);
    freeChunk(&chunk);

//    uint24_t test = convertTo(123456U);
//    printf("sizeof: %d, value: %d\n", sizeof(test), convertBack(test));

    return 0;
}
