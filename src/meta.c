//
// Created by mkuja on 11.5.2022.
//

#include "stdlib.h"
#include "meta.h"
#include "memory.h"

void initLineRle(LinesRle* lineMeta) {
    lineMeta->capacity = 0;
    lineMeta->count = 0;
    lineMeta->lines = NULL;
}

void freeLineRle(LinesRle* lineMeta) {
    FREE_ARRAY(LineMeta, lineMeta->lines, lineMeta->capacity);
}

void incrementLineRle(LinesRle* lines, int line) {
    if (lines->count + 1 > lines->capacity) {
        int oldCapacity = lines->capacity;
        int newCapacity = GROW_CAPACITY(lines->capacity);
        LineMeta* newArr = GROW_ARRAY(LineMeta, lines->lines, oldCapacity, newCapacity);
        if (newArr == NULL) exit(1);
        lines->capacity = newCapacity;
        lines->lines = newArr;
    }

    for (int i = lines->count - 1; i >= 0; i--) {
        if (line == lines->lines[i].lineNum) {
            lines->lines[i].bytesOffset++;
            return;
        }
    }

    lines->lines[lines->count].bytesOffset++;
    lines->lines[lines->count].lineNum = line;
    lines->count++;
}

int getLine(LinesRle* lines, size_t offset) {
    int numBytes = 0;
    for (int i = 0; i < lines->count; i++) {
        numBytes += lines->lines[i].bytesOffset;
        if (offset < numBytes) {
            return lines->lines[i].lineNum;
        }
    }
    return -1;  // Error
}
