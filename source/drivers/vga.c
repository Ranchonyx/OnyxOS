#include "vga.h"


void clrscr(int color)
{
	for(int i = 0; i < COLS_MAX * ROWS_MAX; ++i) {
		set_char_at(i * 2, ' ', color);
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

void set_char_at(int offset, const char chr, const char color)
{
	unsigned char *vidmem = (unsigned char *) VIDMEM_ADDR;
	vidmem[offset] = chr;
	vidmem[offset + 1] = color;
}

void print_string(const char *str)
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
		set_char_at(offset, str[i], ((unsigned char*)VIDMEM_ADDR)[offset + 1]);
		offset += 2;
		}
	i++;
	}
	set_cursor(offset);
}

void println_string(const char *str)
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
		set_char_at(offset, str[i], ((unsigned char*)VIDMEM_ADDR)[offset + 1]);
		offset += 2;
		}
	i++;
	}
	offset = move_offset_to_newline(offset);
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
		set_char_at(get_offset(col, ROWS_MAX - 1), ' ', ((unsigned char*)VIDMEM_ADDR)[offset + 1]);
	}

	return offset - 2 * COLS_MAX;
}

void pixel(unsigned char* screen, int x, int y, int pixelwidth, int pitch, int color) {
    unsigned where = x*pixelwidth + y*pitch;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}
