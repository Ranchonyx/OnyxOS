#include "ports.h"

unsigned char inb( uint16_t port)
{
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a"(result) : "d" (port));
	return result;
}

void outb(uint16_t port, uint8_t data)
{
	__asm__("out %%al, %%dx" : : "a"(data), "d" (port));
	__asm__("out %%al, %%dx" : : "a"(data), "d" (port));
}

unsigned short inw(uint16_t port)
{
	unsigned short result;
	__asm__("in %%dx, %%al" : "=a"(result) : "d" (port));
	return result;
}

void outw(uint16_t port, uint16_t data)
{
	    asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}
