#ifndef __STRING_H__
#define __STRING_H__

#include "stddef.h"

void* memcpy(void* dest, const void* src, size_t n);
void* memmove (void* dest, const void* src, size_t n);
size_t strlen(const char* str);

#endif