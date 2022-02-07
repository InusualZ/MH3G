#pragma once

#include "types.h"

EXPORTED void OSReport (const char* msg, ...);

static void (*OSPanic)(const char* file, int line, const char* msg, ...) = (void(*)(const char*, int, const char*, ...))0x804cd6b0;