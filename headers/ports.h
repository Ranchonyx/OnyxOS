#ifndef PORTS_H
#define PORTS_H
#include "stdint.h"

unsigned char inb( uint16_t port);
void outb(uint16_t port, uint8_t data);
unsigned short inw(uint16_t port);
void outw(uint16_t port, uint16_t data);
#endif /* end of include guard: PORTS_H */
