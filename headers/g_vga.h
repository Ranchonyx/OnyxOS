#ifndef G_VGA_H
#define G_VGA_H
//Graphical VGA driver, only pixels now...

//Screen pixel dimensions
#define RES_HORIZONTAL  640
#define RES_VERTICAL    480
#define RES_TOTAL       (RES_HORIZONTAL * RES_VERTICAL)

//VGA memory address start and end for further usage
#define VGA_MEM_START   0xA0000
#define VGA_MEM_END     0xBFFFF

//Static VGA memory pointer
static unsigned char* __FB__ = (unsigned char*) VGA_MEM_START;

void g_set_pixel(int x, int y, int vga_color);
void g_clrscr();


#endif /* end of include guard: G_VGA_H */
