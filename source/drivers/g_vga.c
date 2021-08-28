#include "g_vga.h"

void g_set_pixel(int x, int y, int vga_color)
{
  __FB__[RES_HORIZONTAL * y + x] = vga_color;
}

void g_clrscr()
{
  for(int i = 0; i < RES_TOTAL; i++) {
    __FB__[i] = 0x0000;
  }
}
