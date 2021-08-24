#include "framebuffer.h"

void writeToFb(size_t offset, const char data, const char color)
{
  __FB__[offset]    = data;
  __FB__[offset+1]  = color;
}

void copyToFB()
{
  memcpy(__FB__, vidmem, FB_SIZE);
}

void copyToVidMem()
{
  memmove(vidmem, __FB__, FB_SIZE);
}

void updateScreen()
{
  copyToVidMem();
  copyToFB();
}
