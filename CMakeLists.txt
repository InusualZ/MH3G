# This file is not acually used to build the project.
# We use CMakeLists to get some intellisense

cmake_minimum_required(VERSION 3.15)
project(MH3G)

set(CMAKE_CXX_STANDARD 20)

# Specify 32-bit processor for better linting
# -Wno-write-strings because some GC SDK functions take non-const char *,
# and Ghidra can't represent const char * anyhow
set(CMAKE_C_FLAGS -m32 -Wno-write-strings)
set(CMAKE_CXX_FLAGS -m32 -Wno-write-strings)

include_directories(rso/include)

add_executable(MH3G
        rso/runtime/restfpr_x.s
        rso/runtime/restgpr_x.s
        rso/cxx.cpp
        rso/heap.cpp
        rso/main.cpp
        rso/patch.cpp
        rso/rso.cpp
        rso/log.cpp
    )
