#ifndef UTIL_H
#define UTIL_H
#include "stdint.h"
#include <stdbool.h>
void itos(int n, char str[]);
void reverse(char s[]);
void delaySeconds(int s);
void printLogo();
char* register_to_string(unsigned reg);
void native_cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t * edx);
char* get_cpu_vendor_string();
bool extended_cpuid_available();
bool is_bit_set(uint32_t val, int bit);
void hang();
#endif /* end of include guard: UTIL_H */
