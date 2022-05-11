//
// Created by mkuja on 11.5.2022.
//

#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif //CLOX_DEBUG_H
