//
// Created by paul on 27/05/2021.
//

#ifndef LOXCOMPILER_OBJECT_H
#define LOXCOMPILER_OBJECT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "value.h"
#include "chunk.h"
#include "table.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC MACROS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OBJ_TYPE(value)         (AS_OBJ(value)->type)

#define IS_BOUND_METHOD(value)  is_obj_tyoe(value, OBJ_BOUND_METHOD)
#define IS_CLASS(value)         is_obj_type(value, OBJ_CLASS)
#define IS_CLOSURE(value)       is_obj_type(value, OBJ_CLOSURE)
#define IS_FUNCTION(value)      is_obj_type(value, OBJ_FUNCTION)
#define IS_INSTANCE(value)      is_obj_type(value, OBJ_INSTANCE)
#define IS_NATIVE(value)        is_obj_type(value, OBJ_NATIVE)
#define IS_STRING(value)        is_obj_type(value, OBJ_STRING)

#define AS_BOUND_METHOD(value)  ((ObjBoundMethod*)AS_OBJ(value))
#define AS_CLASS(value)         ((ObjClass*)AS_OBJ(value))
#define AS_CLOSURE(value)       ((ObjClosure*)AS_OBJ(value))
#define AS_FUNCTION(value)      ((ObjFunction*)AS_OBJ(value))
#define AS_INSTANCE(value)      ((ObjInstance*)AS_OBJ(value))
#define AS_NATIVE(value)        (((ObjNative*)AS_OBJ(value))->function)
#define AS_STRING(value)        ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)       (((ObjString*)AS_OBJ(value))->chars)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC TYPES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum ObjType {
    OBJ_BOUND_METHOD,
    OBJ_CLASS,
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_INSTANCE,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE
} ObjType;

typedef struct Obj {
    ObjType type;
    bool is_marked;
    struct Obj* next;
} Obj;

typedef struct ObjFunction {
    Obj obj;
    int arity;
    int upvalue_count;
    Chunk chunk;
    ObjString* name;
} ObjFunction;

typedef Value (*NativeFn)(int arg_count, Value* args);

typedef struct ObjNative {
    Obj obj;
    NativeFn function;
} ObjNative;

typedef struct ObjString {
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
} ObjString;

typedef struct ObjUpvalue {
    Obj obj;
    Value* location;
    Value closed;
    struct ObjUpvalue* next;
} ObjUpvalue;

typedef struct ObjClosure {
    Obj obj;
    ObjFunction* function;
    ObjUpvalue** upvalues;
    int upvalue_count;
} ObjClosure;

typedef struct ObjClass {
    Obj obj;
    ObjString* name;
    Table methods;
} ObjClass;

typedef struct ObjInstance {
    Obj obj;
    ObjClass* klass;
    Table fields;
} ObjInstance;

typedef struct ObjBoundMethod {
    Obj obj;
    Value receiver;
    ObjClosure* method;
} ObjBoundMethod;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTION DECLARATIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ObjString* copy_string(const char* chars, int length);
ObjBoundMethod* new_bound_method(Value receiver, ObjClosure* method);
ObjClass* new_class(ObjString* name);
ObjClosure* new_closure(ObjFunction* function);
ObjFunction* new_function();
ObjInstance* new_instance(ObjClass* klass);
ObjNative* new_native(NativeFn function);
ObjUpvalue* new_upvalue(Value* slot);
void print_object(Value value);
ObjString* take_string(char* chars, int length);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INLINE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static inline bool is_obj_type(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif //LOXCOMPILER_OBJECT_H
