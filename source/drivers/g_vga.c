#include "g_vga.h"
#include "util.h"
#include "math.h"

void g_set_pixel(int x, int y, uint16_t vga_color)
{
  __FB__[RES_HORIZONTAL * y + x] = vga_color;
}

void g_clrscr()
{
  for(int i = 0; i < RES_TOTAL; i++) {
    __FB__[i] = 0x0000;
  }
}

void g_rect(int x0, int y0, int x1, int y1, uint16_t vga_color)
{

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
    for(int x = x0; x < x1; x++) {
      for(int y = y0; y < y1; y++) {
        g_set_pixel(x, y, vga_color);
      }
    }
}

void g_poly(ipoint_t* points, size_t count, uint16_t vga_color)
{

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

void g_circle(int cx, int cy, int r, uint16_t vga_color)
{
  int x = 0;
  int y = r;
  int d = 3 - 2 * r;

  g_set_pixel(cx+x, cy+y, vga_color);
	g_set_pixel(cx-x, cy+y, vga_color);
	g_set_pixel(cx+x, cy-y, vga_color);
	g_set_pixel(cx-x, cy-y, vga_color);
	g_set_pixel(cx+y, cy+x, vga_color);
	g_set_pixel(cx-y, cy+x, vga_color);
	g_set_pixel(cx+y, cy-x, vga_color);
	g_set_pixel(cx-y, cy-x, vga_color);

  while(y >= x)
  {
    x++;

    if(d > 0) {
      y--;
      d = d + 4 * (x-y) + 10;
    } else {
      d = d + 4 * x + 6;
      g_set_pixel(cx+x, cy+y, vga_color);
      g_set_pixel(cx-x, cy+y, vga_color);
      g_set_pixel(cx+x, cy-y, vga_color);
      g_set_pixel(cx-x, cy-y, vga_color);
      g_set_pixel(cx+y, cy+x, vga_color);
      g_set_pixel(cx-y, cy+x, vga_color);
      g_set_pixel(cx+y, cy-x, vga_color);
      g_set_pixel(cx-y, cy-x, vga_color);

    }
  }

}
