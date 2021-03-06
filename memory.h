//
// Created by paul on 25/05/2021.
//

#ifndef LOXCOMPILER_MEMORY_H
#define LOXCOMPILER_MEMORY_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "object.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC MACROS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type) * (count));

#define FREE(type, pointer) \
    reallocate(pointer, sizeof(type), 0);

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
    (type*)reallocate(pointer, sizeof(type) * (old_count), \
        sizeof(type) * (new_count))

#define FREE_ARRAY(type, pointer, old_count) \
    reallocate(pointer, sizeof(type) * (old_count), 0)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTION DECLARATIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void collect_garbage();
void free_objects();
void mark_object(Obj* object);
void mark_value(Value value);
void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif //LOXCOMPILER_MEMORY_H
