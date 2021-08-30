#include "vga.h"
#include "string.h"
#include "ports.h"
#include "util.h"
#include "sys.h"

void clrscr()
{
	for(size_t i = 0; i < COLS_MAX * ROWS_MAX; ++i) {
		set_char_at(i * 2, ' ', get_color(VIDMEM_SIZE));
	}
	set_cursor(get_offset(0, 0));
}

void set_cursor(size_t offset)
{
	offset /= 2;
	outb(VGA_CTRL_REG, VGA_OFFSET_HIGH);
	outb(VGA_DATA_REG, (unsigned char) (offset >> 8));
	outb(VGA_CTRL_REG, VGA_OFFSET_LOW);
	outb(VGA_DATA_REG, (unsigned char) (offset & 0xFF));
}

size_t get_cursor()
{
	outb(VGA_CTRL_REG, VGA_OFFSET_HIGH);
	size_t offset = inb(VGA_DATA_REG) << 8;
	outb(VGA_CTRL_REG, VGA_OFFSET_LOW);
	offset += inb(VGA_DATA_REG);
	return offset * 2;
}

size_t get_color(size_t offset) {
	return ((unsigned char*) VIDMEM_ADDR)[offset];
}

void set_char_at(size_t offset, const char chr, const char color)
{
	vidmem[offset] = chr;
	vidmem[offset + 1] = color;
}

void set_char_xy(size_t x, size_t y, const char chr, const char color)
{
	vidmem[(x*2) + (COLS_MAX * y * 2)] = chr;
	vidmem[(x*2) + (COLS_MAX * y * 2) + 1] = color;
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
		set_char_at(offset, str[i], get_color(get_cursor()+1));
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
		set_char_at(offset, str[i], get_color(get_cursor()+1));
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

void print_backspace()
{
	set_cursor(get_cursor() - 2);
	set_char_at(get_cursor(), ' ', get_color(get_cursor() + 1));
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
