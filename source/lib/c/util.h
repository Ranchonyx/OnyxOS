#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <time.h>

void memcpy(char *src, char *dst, int n);
void itos(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void delaySeconds(int s);
#endif /* end of include guard: UTIL_H */
