#include "vga.h"
#include "string.h"
#include "ports.h"

void clrscr(const char color)
{
	for(size_t i = 0; i < COLS_MAX * ROWS_MAX; ++i) {
		set_char_at(i * 2, ' ', color);
	}
	set_cursor(get_offset(0, 0));
}

void set_cursor(size_t offset)
{
	offset /= 2;
	out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
	out(VGA_DATA_REG, (unsigned char) (offset >> 8));
	out(VGA_CTRL_REG, VGA_OFFSET_LOW);
	out(VGA_DATA_REG, (unsigned char) (offset & 0xFF));
}

size_t get_cursor()
{
	out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
	size_t offset = in(VGA_DATA_REG) << 8;
	out(VGA_CTRL_REG, VGA_OFFSET_LOW);
	offset += in(VGA_DATA_REG);
	return offset * 2;
}

void set_char_at(size_t offset, const char chr, const char color)
{
	unsigned char *vidmem = (unsigned char *) VIDMEM_ADDR;
	vidmem[offset] = chr;
	vidmem[offset + 1] = color;
}

void print_string(const char *str)
{
	size_t offset = get_cursor();
	size_t i = 0;
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

void print_string_color(const char* str, const char color)
{
	size_t offset = get_cursor();
	size_t i = 0;
	while(str[i] != 0) {
		if(offset >= ROWS_MAX * COLS_MAX * 2) {
			offset = scroll_ln(offset);
		}
		if(str[i] == '\n') {
			offset = move_offset_to_newline(offset);
		} else {
		set_char_at(offset, str[i], color);
		offset += 2;
		}
	i++;
	}
	set_cursor(offset);
}

void println_string(const char *str)
{
	size_t offset = get_cursor();
	size_t i = 0;
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

void println_string_color(const char *str, const char color)
{
	size_t offset = get_cursor();
	size_t i = 0;
	while(str[i] != 0) {
		if(offset >= ROWS_MAX * COLS_MAX * 2) {
			offset = scroll_ln(offset);
		}
		if(str[i] == '\n') {
			offset = move_offset_to_newline(offset);
		} else {
		set_char_at(offset, str[i], color);
		offset += 2;
		}
	i++;
	}
	offset = move_offset_to_newline(offset);
	set_cursor(offset);
}

size_t row_from_offset(size_t offset)
{
	return offset / (2 * COLS_MAX);
}

size_t get_offset(size_t col, size_t row)
{
	return 2 * (row * COLS_MAX + col);
}

size_t move_offset_to_newline(size_t offset)
{
	return get_offset(0, row_from_offset(offset) + 1);
}

int scroll_ln(size_t offset)
{
	memcpy(
		(char *) (get_offset(0, 1) + VIDMEM_ADDR),
		(char *) (get_offset(0, 0) + VIDMEM_ADDR),
		COLS_MAX * (ROWS_MAX - 1) * 2
	);

	for(size_t col = 0; col < COLS_MAX; col++) {
		set_char_at(get_offset(col, ROWS_MAX - 1), ' ', ((unsigned char*)VIDMEM_ADDR)[offset + 1]);
	}

	return offset - 2 * COLS_MAX;
}

void pixel(unsigned char* screen, size_t x, size_t y, size_t pixelwidth, int pitch, color rgb) {
    size_t where = x*pixelwidth + y*pitch;
    screen[where] = rgb.blue;                 // BLUE
    screen[where + 1] = rgb.green;            // GREEN
    screen[where + 2] = rgb.red;              // RED
}

void color_test()
{
	char color = 0x00;
	char _color = 0xf0;
	for(int i = 0; i < 256; i++) {
		print_string_color("#", color+_color);
		color++;
		_color++;
	}
}
