#include "sys.h"

#define VIDMEM_START  0x000a0000
#define VIDMEM_END    0x000BFFFF
#define FB_SIZE       (VIDMEM_END - VIDMEM_START)


//Pointer to the start of vga video memory
unsigned char *vidmem = (unsigned char *) VIDMEM_START;
unsigned char __FB__[FB_SIZE];

void writeToFb(size_t offset, const char data, const char color);
void copyToFB();
void copyToVidMem();
void updateScreen();
