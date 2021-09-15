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
// #define RES_HORIZONTAL 1024
// #define RES_VERTICAL   768

//Total resolution, also in bytes
#define RES_TOTAL       (RES_HORIZONTAL * RES_VERTICAL)

//VGA memory address start and end for further usage
#define VGA_MEM_START   0xA0000
#define VGA_MEM_END     0xBFFFF

//Static VGA memory pointer
static unsigned char* __FB__ = (unsigned char*) VGA_MEM_START;

//Static cursor location
static ipoint_t _cursor;

//Static graphics_mode variable, 0 disable drawing mode, 1 enable drawing mode
static int graphics_mode = 0;

//Initialize VGA cursor at 0,0
void init_vga();

//Toggle graphics_mode from 0 -> 1 | 1 -> 0 respectively
void g_toggle_graphics_mode();

//Set a pixel to a certain color at location x,y
void g_set_pixel(int x, int y, uint16_t vga_color);

//Returns the color of a pixel at location x,y
uint16_t g_get_color(int x, int y);

//Clear the entire screen
void g_clrscr();

//Draw a rectangle from x0,y0 to x1,y1 using a color
void g_rect(int x0, int y0, int x1, int y1, uint16_t vga_color);

//Same as above but fill the rectangle in a color
void g_fill_rect(int x0, int y0, int x1, int y1, uint16_t vga_color);

//Draw a Polygon from an array of points using a color
void g_poly(ipoint_t* points, size_t count, uint16_t vga_color);

//Draw a line from x0,y0 to x1,y1 using a color
void g_line(int x0, int y0, int x1, int y1, uint16_t vga_color);

//Draw a circle at cx, cy with the radius r using a color
void g_circle(int cx, int cy, int r, uint16_t vga_color);

//Set a font character at x,y using a color while keeping the background
void g_t_set_char(char c, int x, int y, uint16_t fgcolor);

//Print a string at the current cursor position using a color while keeping the background
void g_t_print_string(const char* str, uint16_t fgcolor);

//Set a font character at x,y using a color
void g_set_char(const char c, int x, int y, uint16_t fgcolor, uint16_t bgcolor);

//Print a string at the current cursor position using a color
void g_print_string(const char* str, uint16_t fgcolor, uint16_t bgcolor);

//Print a backspace at current cursor position
void g_print_backspace();

//Scroll the screen by 8 pixels
void g_scroll_ln();

//Return the framebuffer offset at location x,y
int  g_get_offset(int x, int y);

//Print a newline character at the current cursor position
void g_print_newline();

#endif /* end of include guard: G_VGA_H */
