#include "util.h"
#include "string.h"
#include "stddef.h"
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

//Literally Fast-Nop's C incarnation
void delaySeconds(int s)
{
	long time = (100000000 * s) / 2;
	for(volatile int i = 0; i < time ; i++) {
		__asm volatile ("nop" : : : "memory");
	}
}

void printLogo()
{
	println_string_color("     _/_/                                    _/_/      _/_/_/   ", YELLOW_ON_BLACK);
	println_string_color("  _/    _/  _/_/_/    _/    _/  _/    _/  _/    _/  _/          ", YELLOW_ON_BLACK);
	println_string_color(" _/    _/  _/    _/  _/    _/    _/_/    _/    _/    _/_/       ", YELLOW_ON_BLACK);
	println_string_color("_/    _/  _/    _/  _/    _/  _/    _/  _/    _/        _/      ", YELLOW_ON_BLACK);
	println_string_color(" _/_/    _/    _/    _/_/_/  _/    _/    _/_/    _/_/_/         ", YELLOW_ON_BLACK);
	println_string_color("                        _/                                      ", YELLOW_ON_BLACK);
	println_string_color("                   _/_/                                         ", YELLOW_ON_BLACK);
}

//Linux Kernel implementation
void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
        /* ecx is often an input as well as an output. */
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}


//Special thanks to Fast-Nop for the char extraction help and patience with me
char *register_to_string(unsigned reg)
{
	char regtext[4];
	char* regtext_ptr = regtext;
	char c1 = (char) (reg >> 24);
	char c2 = (char) ((reg >> 16) & 0xFF);
	char c3 = (char) ((reg >> 8) & 0xFF);
	char c4 = (char) reg;

	regtext[0] = c1;
	regtext[1] = c2;
	regtext[2] = c3;
	regtext[3] = c4;
	regtext[4] = '\0';


	reverse(regtext);
	return regtext_ptr;
}

//Returns the CPU vendor string, glaube ich
char* get_cpu_vendor_string()
{
	unsigned eax, ebx, ecx, edx;
	eax = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	//EBX;EDX;ECX
	char *output = "";
	strcat(output, register_to_string(ebx));
	strcat(output, register_to_string(edx));
	strcat(output, register_to_string(ecx));

	return (char*) output;

}
