#ifndef G_VGA_H
#define G_VGA_H

#include "stdint.h"
#include "stddef.h"
#include "math.h"

//Graphical VGA driver, only pixels now...

//Screen pixel dimensions
#define RES_HORIZONTAL  320
#define RES_VERTICAL    200
#define RES_TOTAL       (RES_HORIZONTAL * RES_VERTICAL)

//VGA memory address start and end for further usage
#define VGA_MEM_START   0xA0000
#define VGA_MEM_END     0xBFFFF

//Static VGA memory pointer
static unsigned char* __FB__ = (unsigned char*) VGA_MEM_START;

void g_set_pixel(int x, int y, uint16_t vga_color);
void g_clrscr();
void g_rect(int x0, int y0, int x1, int y1, uint16_t vga_color);
void g_fill_rect(int x0, int y0, int x1, int y1, uint16_t vga_color);
void g_poly(ipoint_t* points, size_t count, uint16_t vga_color);
void g_line(int x0, int y0, int x1, int y1, uint16_t vga_color);

#endif /* end of include guard: G_VGA_H */
