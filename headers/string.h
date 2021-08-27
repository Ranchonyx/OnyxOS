#ifndef __STRING_H__
#define __STRING_H__

#include "stddef.h"


size_t strlen(const char* str);
char* strcat(char* dest, char* src);
void append(char s[], char c);
void lower(char s[]);
int compare_string(char s1[], char s2[]);
int backspace(char s[]);
#endif
