#ifndef TEXTMODE_GFX_H
#define TEXTMODE_GFX_H
#include "stdint.h"
#include "stddef.h"

void line(size_t sx, size_t sy, size_t ex, size_t ey, const char chr, const char color);
void rect(size_t sx, size_t sy, size_t ex, size_t ey, const char chr, const char color);
void fill_rect(size_t sx, size_t sy, size_t ex, size_t ey, const char chr, const char color);

#endif /* end of include guard: TEXTMODE_GFX_H */
