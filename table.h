//
// Created by paul on 04/06/2021.
//

#ifndef LOXCOMPILER_TABLE_H
#define LOXCOMPILER_TABLE_H

#include "common.h"
#include "value.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC TYPES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Entry {
    ObjString* key;
    Value value;
} Entry;

typedef struct Table {
    int count;
    int capacity;
    Entry* entries;
} Table;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTION DECLARATIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_table(Table* table);
void init_table(Table* table);
void mark_table(Table* table);
void table_add_all(Table* from, Table* to);
bool table_delete(Table* table, ObjString* key);
ObjString* table_find_string(Table* table, const char* chars, int length, uint32_t hash);
bool table_get(Table* table, ObjString* key, Value* value);
void table_remove_white(Table* table);
bool table_set(Table* table, ObjString* key, Value value);

#endif //LOXCOMPILER_TABLE_H
