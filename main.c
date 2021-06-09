#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl() {
    char line[1024];
    for(;;) {
        printf("> ");

        if(!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        
        interpret(line);
    }
}

static char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");
    if(file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* buffer = (char*) malloc(file_size + 1);
    if(buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }
    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if(bytes_read < file_size) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }


    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}

static void run_file(const char* path) {
    char* source = read_file(path);
    InterpretResult result = interpret(source);
    free(source);

    if(result == INTERPRET_COMPILE_ERROR) exit(65);
    if(result == INTERPRET_RUNTIME_ERROR) exit(70);
}

static Value clock_native(int arg_count, Value* args) {
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}

static void print_native_function(const char* name, int arg_count, Value* args) {
    printf("Native Function Call: %s\n", name);
    printf("   Number of Args: %d\n", arg_count);
    for(int i = 0; i < arg_count; i++) {
        printf("      ");
        print_value(args[i]);
        printf("\n");
    }
}

static Value expect_native(int arg_count, Value* args) {
    print_native_function("expect", arg_count, args);
    return NUMBER_VAL(0);
}

static Value expectre_native(int arg_count, Value* args) {
    print_native_function("expectre", arg_count, args);
    return NUMBER_VAL(0);
}

static Value sleep_native(int arg_count, Value* args) {
    print_native_function("sleep", arg_count, args);
    return NIL_VAL;
}

static Value launch_native(int arg_count, Value* args) {
    print_native_function("launch", arg_count, args);
    return BOOL_VAL(true);
}

static Value send_native(int arg_count, Value* args) {
    print_native_function("send", arg_count, args);
    return NIL_VAL;
}

static Value sendline_native(int arg_count, Value* args) {
    print_native_function("sendline", arg_count, args);
    return NIL_VAL;
}

int main(int argc, const char* argv[]) {
    init_vm();
    define_native("clock", clock_native);
    define_native("expect", expect_native);
    define_native("expectre", expectre_native);
    define_native("sleep", sleep_native);
    define_native("launch", launch_native);
    define_native("send", send_native);
    define_native("sendline", sendline_native);
/*
    if(argc == 1) {
        repl();
    } else if(argc == 2) {
        run_file(argv[1]);
    } else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }
*/
    run_file("/home/paul/CLionProjects/LoxCompiler/test.txt");
    free_vm();
    return 0;
}
