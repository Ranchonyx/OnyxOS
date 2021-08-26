#include "vga.h"
#include "string.h"
#include "ports.h"
#include "util.h"
#include "sys.h"

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

size_t get_color(size_t offset) {
	return ((unsigned char*) VIDMEM_ADDR)[offset];
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
		set_char_at(offset, str[i], WHITE_ON_BLACK/*((unsigned char*)VIDMEM_ADDR)[offset + 1]*/);
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
	memmove(
		(uint8_t *) (get_offset(0, 0) + VIDMEM_ADDR),
		(uint8_t *) (get_offset(0, 1) + VIDMEM_ADDR),
		(COLS_MAX * (ROWS_MAX - 1) * 2)
	);

	for(size_t col = 0; col < COLS_MAX; col++) {
		set_char_at(get_offset(col, ROWS_MAX - 1), ' ', ((unsigned char*)VIDMEM_ADDR)[offset + 1]);
	}

	return offset - 2 * COLS_MAX;
}

void color_test()
{
	const char d[2] = {(char)176, '\0'};
	char color = 0x00;
	char _color = 0xf0;
	for(int i = 0; i < 256; i++) {
		print_string_color(d, color+_color);
		color++;
		_color++;
	}
}
