cmake_minimum_required(VERSION 3.19)
project(LoxCompiler C)

set(CMAKE_C_STANDARD 99)

add_executable(LoxCompiler main.c common.h chunk.h chunk.c memory.h memory.c debug.h debug.c value.h value.c vm.h vm.c compiler.h compiler.c scanner.h scanner.c object.h object.c table.h table.c)