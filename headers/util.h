#ifndef UTIL_H
#define UTIL_H
#include "stdint.h"
void itos(int n, char str[]);
void reverse(char s[]);
void delaySeconds(int s);
void printLogo();
char* register_to_string(unsigned reg);
void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int * edx);
char* get_cpu_vendor_string();
#endif /* end of include guard: UTIL_H */
