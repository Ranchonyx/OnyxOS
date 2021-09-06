#ifndef G_VGA_H
#define G_VGA_H

#include "stdint.h"
#include "stddef.h"
#include "math.h"

//Graphical VGA driver, only pixels now...

//Screen pixel dimensions
#define RES_HORIZONTAL  320
#define RES_VERTICAL    200
// #define RES_HORIZONTAL  640
// #define RES_VERTICAL    480


#define RES_TOTAL       (RES_HORIZONTAL * RES_VERTICAL)

//VGA memory address start and end for further usage
#define VGA_MEM_START   0xA0000
#define VGA_MEM_END     0xBFFFF

//Static VGA memory pointer
static unsigned char* __FB__ = (unsigned char*) VGA_MEM_START;
ipoint_t _cursor;


void init_vga();
void g_set_pixel(int x, int y, uint16_t vga_color);
uint16_t g_get_color(int x, int y);
void g_clrscr();
void g_rect(int x0, int y0, int x1, int y1, uint16_t vga_color);
void g_fill_rect(int x0, int y0, int x1, int y1, uint16_t vga_color);
void g_poly(ipoint_t* points, size_t count, uint16_t vga_color);
void g_line(int x0, int y0, int x1, int y1, uint16_t vga_color);
void g_circle(int cx, int cy, int r, uint16_t vga_color);
void g_set_char(const char c, int x, int y, uint16_t fgcolor, uint16_t bgcolor);
void g_print_string(const char* str, uint16_t fgcolor, uint16_t bgcolor);
void g_print_backspace();
void g_scroll_ln();
int  g_get_offset(int x, int y);

#endif /* end of include guard: G_VGA_H */
