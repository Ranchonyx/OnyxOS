#define VGA_CTRL_REG		0x3D4
#define VGA_DATA_REG		0x3D5
#define VGA_OFFSET_LOW		0x0F
#define VGA_OFFSET_HIGH		0x0E

#define VIDMEM_ADDR		0xb8000
#define ROWS_MAX		25
#define COLS_MAX		80

#define WHITE_ON_BLACK		0x0f


void 	clrscr();
void	set_cursor(int offset);
int	get_cursor();
void	set_char_at_offset(char chr, int offset);
void	print_string(char *str);
int	row_from_offset(int offset);
int	get_offset(int col, int row);
int	move_offset_to_newline(int offset);
int	scroll_ln(int offset);
