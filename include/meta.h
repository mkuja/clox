//
// Created by mkuja on 11.5.2022.
//

#ifndef CLOX_META_H
#define CLOX_META_H

#include <stdint.h>

typedef struct {
    int lineNum;
    int bytesOffset;
} LineMeta;

typedef struct {
    int count;
    int capacity;
    LineMeta* lines;
} LinesRle;

void initLineRle(LinesRle* lines);
void freeLineRle(LinesRle* lines);
void incrementLineRle(LinesRle* lines, int line);
int getLine(LinesRle* lines, size_t offset);

#endif //CLOX_META_H
