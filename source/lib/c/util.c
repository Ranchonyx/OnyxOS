#include "util.h"
#include "string.h"
#include "stddef.h"
#include "stdint.h"
#include "vga.h"
#include "timer.h"

void reverse(char s[])
{
	int g, numb;
	int tmpry = 0;

	for(numb=0; s[numb] != 0; numb++);
	
	for(g = 0; g <numb/2; g++)
	{
			tmpry = s[g];
			s[g]=s[numb - 1 - g];
			s[numb - 1 - g] = tmpry;
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
		for(int j = 0; i < cols; j++) {
			//DEBUG
			dest[i * cols + j] = src[i][j];
		}
	}
}

//Literally Fast-Nop's C incarnation
// void delaySeconds(int s)
// {
// 	long time = (100000000 * s) / 2;
// 	for(volatile int i = 0; i < time; i++) {
// 		__asm volatile ("nop" : : : "memory");
// 	}
// }

//New delay implementation
//For some reason doesnt work everywhere i dunno bro
//For some reason doesnt work everywhere i dunno bro


bool is_bit_set(uint32_t val, int bit)
{
	if(val & (1 << bit)) {
		return true;
	} else {
		return false;
	}
	return false;
}

int abs(int x)
{
	int t = (unsigned int) x >> 31;
	return (- t) ^ (x - t);
}

double pow(double base, double exponent)
{
	double r = 1;

	for(exponent; exponent > 0; exponent--) {
		r *= base;
	}

	return r;
}

	double sqrt(double x)
	{
		double r = x;

		__asm__ volatile("fsqrt" : "+t"(r));

		return r;
	}

double sin(double x)
{
	double r = x;

	__asm__ volatile("fsin" : "+t"(r));

	return r;
}

double cos(double x)
{
	return sin(1.5708 + x);
}

double tan(double x)
{
	return sin(x)/sin(1.5708 + x);
}

uint32_t hwrand32()
{
	uint32_t v;
	__asm__ volatile("rdrand %0" : "=a"(v)::);
	return v;
}

uint16_t hwrand16()
{
	return (uint16_t) hwrand32();
}

uint8_t hwrand8()
{
	return (uint8_t) hwrand32();
}
