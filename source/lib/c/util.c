#include "util.h"
#include "string.h"
#include "stddef.h"

void reverse(char s[])
{
	char c;
	size_t i, j;
	for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itos(int n, char str[])
{
	size_t i;
	int sign;
	if((sign = n) < 0) n = -n;
	
	i = 0;
	do {
		str[i++] = n % 10 + '0';
	} while((n /= 10) > 0);

	if(sign < 0) str[i++] = '-';
	str[i] = '\0';

	reverse(str);
}

//Literally Fast-Nop's C incarnation
void delaySeconds(int s)
{
	long time = (100000000 * s) / 2;
	for(volatile int i = 0; i < time ; i++) {
		__asm volatile ("nop" : : : "memory");
	}
}
