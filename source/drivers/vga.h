#ifndef VGA_H
#define VGA_H
#include <stdint.h>
#include "ports.h"
#include "../lib/c/util.h"

#define VGA_CTRL_REG		0x3D4
#define VGA_DATA_REG		0x3D5
#define VGA_OFFSET_LOW		0x0F
#define VGA_OFFSET_HIGH		0x0E

#define VIDMEM_ADDR		0xb8000
#define ROWS_MAX		25
#define COLS_MAX		80

#define BLUE_ON_BLACK     0x01
#define GREEN_ON_BLACK    0x02
#define RED_ON_BLACK      0x04
#define PURPLE_ON_BLACK   0x05
#define WHITE_ON_BLACK		0x0f

void 	clrscr(int color);
void	set_cursor(int offset);
int	  get_cursor();
void	set_char_at(int offset, const char chr, const char color);
void	print_string(const char *str);
void	println_string(const char *str);
int	  row_from_offset(int offset);
int	  get_offset(int col, int row);
int	  move_offset_to_newline(int offset);
int	  scroll_ln(int offset);
void  pixel(unsigned char* screen, int x, int y, int pixelwidth, int pitch, int color);
#endif /* end of include guard: VGA_H */
