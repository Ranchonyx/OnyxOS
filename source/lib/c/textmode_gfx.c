#include "textmode_gfx.h"
#include "stdint.h"
#include "stddef.h"
#include "vga.h"
#include "util.h"

void line(size_t x0, size_t y0, size_t x1, size_t y1, const char chr, const char color)
{
  // size_t dx = ex - sx;
  // size_t dy = ey - sy;
  //
  // size_t d = 2*dy - dx;
  //
  // size_t y = sy;
  //
  // for(int x = sx; x < ex; x++) {
  //   set_char_xy(x, y, chr, color);
  //   if(d > 0) {
  //     y = y + 1;
  //     d = d - 2*dx;
  //   }
  //   d = 2 + 2*dy;
  // }

  int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy =  -abs(y1-y0), sy = y0<y1 ? 1 : -1;

  int err = dx+dy, e2;

  while (1) {
    set_char_xy(x0, y0, chr, color);
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

void rect(size_t sx, size_t sy, size_t ex, size_t ey, const char chr, const char color)
{
  for(size_t x = sx; x < ex; x++) {
    for(size_t y = sy; y < ey; y++) {
      set_char_xy(x, y, chr, color);
    }
  }
  for(size_t x = sx+1; x < ex-1; x++) {
    for(size_t y = sy+1; y < ey-1; y++) {
      set_char_xy(x, y, ' ', color);
    }
  }
}

void fill_rect(size_t sx, size_t sy, size_t ex, size_t ey, const char chr, const char color)
{
  for(size_t x = sx; x < ex; x++) {
    for(size_t y = sy; y < ey; y++) {
      set_char_xy(x, y, chr, color);
    }
  }
}
