#include "vga.h"
#include "ports.h"
#include "util.h"

void clrscr()
{
	for(int i = 0; i < COLS_MAX * ROWS_MAX; ++i) {
		set_char_at_offset(' ', i * 2);
	}
	set_cursor(get_offset(0, 0));
}


void set_cursor(int offset)
{
	offset /= 2;
	out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
	out(VGA_DATA_REG, (unsigned char) (offset >> 8));
	out(VGA_CTRL_REG, VGA_OFFSET_LOW);
	out(VGA_DATA_REG, (unsigned char) (offset & 0xFF));
}

int get_cursor()
{
	out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
	int offset = in(VGA_DATA_REG) << 8;
	out(VGA_CTRL_REG, VGA_OFFSET_LOW);
	offset += in(VGA_DATA_REG);
	return offset * 2;
}

void set_char_at_offset(char chr, int offset)
{
	unsigned char *vidmem = (unsigned char *) VIDMEM_ADDR;
	vidmem[offset] = chr;
	vidmem[offset + 1] = WHITE_ON_BLACK;
}

void print_string(char *str)
{
	int offset = get_cursor();
	int i = 0;
	while(str[i] != 0) {
		if(offset >= ROWS_MAX * COLS_MAX * 2) {
			offset = scroll_ln(offset);
		}
		if(str[i] == '\n') {
			offset = move_offset_to_newline(offset);
		} else {
		set_char_at_offset(str[i], offset);
		offset += 2;
		}
	i++;
	}
	set_cursor(offset);
}

int row_from_offset(int offset)
{
	return offset / (2 * COLS_MAX);
}

int get_offset(int col, int row)
{
	return 2 * (row * COLS_MAX + col);
}

int move_offset_to_newline(int offset)
{
	return get_offset(0, row_from_offset(offset) + 1);
}

int scroll_ln(int offset)
{
	memcpy(
		(char *) (get_offset(0, 1) + VIDMEM_ADDR),
		(char *) (get_offset(0, 0) + VIDMEM_ADDR),
		COLS_MAX * (ROWS_MAX - 1) * 2
	);

	for(int col = 0; col < COLS_MAX; col++) {
		set_char_at_offset(' ', get_offset(col, ROWS_MAX - 1));
	}

	return offset - 2 * COLS_MAX;
}
