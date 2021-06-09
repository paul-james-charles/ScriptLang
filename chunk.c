//
// Created by paul on 25/05/2021.
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SYSTEM INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "chunk.h"
#include "memory.h"
#include "vm.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void init_chunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    init_value_array(&chunk->constants);
}

void free_chunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    free_value_array(&chunk->constants);
    init_chunk(chunk);
}

int add_constant(Chunk* chunk, Value value) {
    push(value);
    write_value_array(&chunk->constants, value);
    pop();
    return chunk->constants.count - 1;
}

void write_chunk(Chunk* chunk, uint8_t byte, int line) {
    if(chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, old_capacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}
