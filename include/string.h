#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str);
int strcmp(const char* str1, const char* str2);
char * itoa( int value, char * str, int base );

#endif