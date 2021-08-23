#ifndef VGA_H
#define VGA_H

#include "stdint.h"
#include "stddef.h"

#define VGA_CTRL_REG		  0x3D4
#define VGA_DATA_REG		  0x3D5
#define VGA_OFFSET_LOW		0x0F
#define VGA_OFFSET_HIGH		0x0E

#define VIDMEM_ADDR		    0xb8000
#define ROWS_MAX		      25
#define COLS_MAX		      80

#define BLUE_ON_BLACK     0x01
#define GREEN_ON_BLACK    0x02
#define CYAN_ON_BLACK     0x03
#define RED_ON_BLACK      0x04
#define PURPLE_ON_BLACK   0x05
#define BROWN_ON_BLACK    0x06
#define LGREY_ON_BLACK    0x07
#define DGREY_ON_BLACK    0x08
#define TEAL_ON_BLACK     0x09
#define EMERALD_ON_BLACK  0x0a
#define LCYAN_ON_BLACK    0x0b
#define LRED_ON_BLACK     0x0c
#define MAGENTA_ON_BLACK  0x0d
#define YELLOW_ON_BLACK   0x0e
#define WHITE_ON_BLACK		0x0f


typedef union {
  uint32_t rgba;
  struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
  };
} color;

void    clrscr(const char color);
void    set_cursor(size_t offset);
size_t  get_cursor();
size_t get_color(size_t offset);
void    set_char_at(size_t offset, const char chr, const char color);
void    print_string_color(const char* str, const char color);
void    print_string(const char *str);
void    println_string(const char *str);
void    println_string_color(const char *str, const char color);
size_t  row_from_offset(size_t offset);
size_t  get_offset(size_t col, size_t row);
size_t  move_offset_to_newline(size_t offset);
int     scroll_ln(size_t offset);
void    pixel(unsigned char* screen, size_t x, size_t y, size_t pixelwidth, int pitch, color rgb);
void    color_test();
#endif /* end of include guard: VGA_H */
