#include "types.h"

EXPORTED void memcpy(void* dest, void* src, size_t size);
EXPORTED void memset(void* dest, void* src, size_t size);

EXPORTED char* strcat(char * destination, const char * source);
EXPORTED char* strchr(const char* str, int character);
EXPORTED int strcmp(const char* str1, const char* str2);
EXPORTED char* strcpy(char* destination, const char* source);
EXPORTED size_t strlen (const char* str);
EXPORTED char* strstr(char* str1, const char* str2);
EXPORTED char* strupr(char* str1);

EXPORTED int sprintf(char * buffer, char * format, ...);
// EXPORTED int vsnprintf (char * s, size_t n, const char * format, va_list arg);
