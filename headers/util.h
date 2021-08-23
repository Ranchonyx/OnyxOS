#ifndef UTIL_H
#define UTIL_H
#include "stdint.h"
#include <stdbool.h>
void itos(int n, char str[]);
void reverse(char s[]);
void delaySeconds(int s);
//void printLogo();
bool is_bit_set(uint32_t val, int bit);
#endif /* end of include guard: UTIL_H */
