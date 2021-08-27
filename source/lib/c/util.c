#include "util.h"
#include "string.h"
#include "stddef.h"
#include "stdint.h"
#include "vga.h"

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

void map_field_to_matrix(unsigned char src[], size_t rows, size_t cols, unsigned char dest[rows][cols])
{
	size_t k = 0;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			//dest[i][j] = src[(j*rows) + i];
			dest[i][j] = src[k];
			k++;
		}
	}
}

void map_matrix_to_field(unsigned char dest[], size_t rows, size_t cols, unsigned char src[rows][cols])
{
	for(int i = 0; i < rows; i++) {
		int row = 0;
		for(int j = 0; i < cols; j++) {
			//DEBUG
			dest[i * cols + j] = src[i][j];
		}
	}
}

//Literally Fast-Nop's C incarnation
void delaySeconds(int s)
{
	long time = (100000000 * s) / 2;
	for(volatile int i = 0; i < time; i++) {
		__asm volatile ("nop" : : : "memory");
	}
}

bool is_bit_set(uint32_t val, int bit)
{
	if(val & (1 << bit)) {
		return true;
	} else {
		return false;
	}
	return false;
}
