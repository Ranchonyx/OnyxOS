#ifndef UTIL_H
#define UTIL_H
#include "stdint.h"
#include "stddef.h"
#include <stdbool.h>
void itos(int n, char str[]);
void reverse(char s[]);
void delaySeconds(int s);
void map_field_to_matrix(unsigned char src[], size_t rows, size_t cols, unsigned char dest[rows][cols]);
void map_matrix_to_field(unsigned char dest[], size_t rows, size_t cols, unsigned char src[rows][cols]);
bool is_bit_set(uint32_t val, int bit);
int  abs(int x);
#endif /* end of include guard: UTIL_H */
