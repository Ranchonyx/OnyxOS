#include "g_vga.h"
#include "util.h"
#include "math.h"
#include "stdint.h"
#include "font.h"
#include "sys.h"

void init_vga()
{
   _cursor.x = 0;
   _cursor.y = 0;
}

void g_toggle_graphics_mode()
{
  // graphics_mode == 1 ? 0 : 1;
  if(graphics_mode == 1) {
    graphics_mode = 0;
  } else if(graphics_mode == 0) {
    graphics_mode = 1;
  } else {
    hang("Invalid Graphics Mode");
  }
}

int g_get_offset(int x, int y)
{
  return RES_HORIZONTAL * y + x;
}

void g_set_pixel(int x, int y, uint16_t vga_color)
{
  __FB__[RES_HORIZONTAL * y + x] = vga_color;
}

uint16_t g_get_color(int x, int y)
{
  return (uint16_t) __FB__[RES_HORIZONTAL * y + x];
}

void g_clrscr()
{
  _cursor.x = 0;
  _cursor.y = 0;
  for(int i = 0; i < RES_TOTAL; i++) {
    __FB__[i] = 0x0000;
  }
}

void g_rect(int x0, int y0, int x1, int y1, uint16_t vga_color)
{
  if(graphics_mode != 1) {
    return;
  }

  ipoint_t p0 = {x0, y0};
  ipoint_t p1 = {x0, y1};
  ipoint_t p2 = {x1, y1};
  ipoint_t p3 = {x1, y0};

  g_line(p0.x, p0.y, p1.x, p1.y, vga_color);
  g_line(p1.x, p1.y, p2.x, p2.y, vga_color);
  g_line(p2.x, p2.y, p3.x, p3.y, vga_color);
  g_line(p3.x, p3.y, p0.x, p0.y, vga_color);

}

void g_fill_rect(int x0, int y0, int x1, int y1, uint16_t vga_color)
{
  if(graphics_mode != 1) {
    return;
  }

    for(int x = x0; x < x1; x++) {
      for(int y = y0; y < y1; y++) {
        g_set_pixel(x, y, vga_color);
      }
    }
}

void g_poly(ipoint_t* points, size_t count, uint16_t vga_color)
{
  if(graphics_mode != 1) {
    return;
  }

  //Polygon can't have less than 3 points / vertices
  if(count < 3) {
    g_set_pixel(0,0, 0x0e);
    return;
  }

  ipoint_t current;
  ipoint_t next;
  ipoint_t last = points[0];
  for(int i = 0; i < count; i++) {
    current = points[i];
    if(i+1 >= count) {
      g_line(current.x, current.y, last.x, last.y, vga_color);
      return;
    }
    next = points[i+1];
    g_line(current.x, current.y, next.x, next.y, vga_color);

  }
}

void g_line(int x0, int y0, int x1, int y1, uint16_t vga_color)
{
  if(graphics_mode != 1) {
    return;
  }

  int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy =  -abs(y1-y0), sy = y0<y1 ? 1 : -1;

  int err = dx+dy, e2;

  while (1) {
    g_set_pixel(x0, y0, vga_color);
    if(x0 == x1 && y0 == y1) break;
    e2 = 2*err;
    if(e2 > dy) {
      err+= dy; x0 += sx;
    }
    if(e2 < dx) {
      err+= dx; y0 += sy;
    }
  }
}

void g_circle(int x0, int y0, int r, uint16_t vga_color)
{
  if(graphics_mode != 1) {
    return;
  }

    int f = 1 - r;
    int ddF_x = 0;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;

    g_set_pixel(x0, y0 + r, vga_color);
    g_set_pixel(x0, y0 - r, vga_color);
    g_set_pixel(x0 + r, y0, vga_color);
    g_set_pixel(x0 - r, y0, vga_color);

    while(x < y)
    {
      if(f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x + 1;

      g_set_pixel(x0 + x, y0 + y, vga_color);
      g_set_pixel(x0 - x, y0 + y, vga_color);
      g_set_pixel(x0 + x, y0 - y, vga_color);
      g_set_pixel(x0 - x, y0 - y, vga_color);
      g_set_pixel(x0 + y, y0 + x, vga_color);
      g_set_pixel(x0 - y, y0 + x, vga_color);
      g_set_pixel(x0 + y, y0 - x, vga_color);
      g_set_pixel(x0 - y, y0 - x, vga_color);
    }
}

void g_set_char(char c, int x, int y, uint16_t fgcolor, uint16_t bgcolor)
{
  const uint8_t *glyph = font[c];
  if( (x > RES_HORIZONTAL || y > RES_VERTICAL) || (x < 0 || y < 0) ) {
    return;
  }

  for(size_t yy = 0; yy < 8; yy++) {
    for(size_t xx = 0; xx < 8; xx++) {
      if(glyph[yy] & (1 << xx)) {
        g_set_pixel(x + xx, y + yy, fgcolor);
      } else {
        g_set_pixel(x + xx, y + yy, bgcolor);
      }
    }
  }
}

void g_t_set_char(char c, int x, int y, uint16_t fgcolor)
{
  const uint8_t *glyph = font[c];
  if( (x > RES_HORIZONTAL || y > RES_VERTICAL) || (x < 0 || y < 0) ) {
    return;
  }

  for(size_t yy = 0; yy < 8; yy++) {
    for(size_t xx = 0; xx < 8; xx++) {
      if(glyph[yy] & (1 << xx)) {
        g_set_pixel(x + xx, y + yy, fgcolor);
      } else {
        g_set_pixel(x + xx, y + yy, g_get_color(x + xx, y + yy));
      }
    }
  }
}

void g_t_print_string(const char* str, uint16_t fgcolor)
{
  int i = 0;
  if(str[0] == '\n' && str[1] == '\0') {
    g_print_newline();
    return;
  }

  while(str[i] != '\0') {


    if(str[i] != '\n') {

            if(_cursor.y >= RES_VERTICAL - 8) {
              g_scroll_ln();
              _cursor.y -= 8;
              _cursor.x = 0;
            }

            if(_cursor.x == RES_HORIZONTAL) {
              g_print_newline();
            }
              g_t_set_char(str[i], _cursor.x, _cursor.y, fgcolor);

              _cursor.x += 8;
            } else {
              g_print_newline();
            }
    i++;

  }
}

void g_print_string(const char* str, uint16_t fgcolor, uint16_t bgcolor)
{
  int i = 0;
  if(str[0] == '\n' && str[1] == '\0') {
    g_print_newline();
    return;
  }

  while(str[i] != '\0') {

    if(str[i] != '\n') {

            if(_cursor.y >= RES_VERTICAL - 8) {
              g_scroll_ln();
              _cursor.y -= 8;
              _cursor.x = 0;
            }

            if(_cursor.x == RES_HORIZONTAL) {
              g_print_newline();
            }
              g_set_char(str[i], _cursor.x, _cursor.y, fgcolor, bgcolor);

              _cursor.x += 8;
            } else {
              g_print_newline();
            }
    i++;

  }
}

void g_scroll_ln()
{
    memmove(
      (uint16_t *) (g_get_offset(0, 0) + VGA_MEM_START),
      (uint16_t *) (g_get_offset(0, 8) + VGA_MEM_START),
      (RES_VERTICAL * (RES_HORIZONTAL - 1))
    );

}

void g_print_newline()
{
  if(_cursor.y >= RES_VERTICAL -8) {
    g_scroll_ln();
  }
  _cursor.x = 0;
  _cursor.y += 8;
}

void g_print_backspace()
{
  if(graphics_mode != 1) {
    g_toggle_graphics_mode();
  }
  _cursor.x = _cursor.x - 8;
  g_fill_rect(_cursor.x, _cursor.y, _cursor.x+8, _cursor.y+8, 0x0);
}
