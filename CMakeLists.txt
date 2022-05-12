cmake_minimum_required(VERSION 3.21)
project(clox C)

set(CMAKE_C_STANDARD 23)


add_executable(clox src/main.c include/common.h include/chunk.h src/chunk.c include/memory.h src/memory.c include/debug.h src/debug.c include/value.h src/value.c include/meta.h src/meta.c include/uint24_t.h src/uint24_t.c include/vm.h src/vm.c)
target_include_directories(clox PRIVATE include)
