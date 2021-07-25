#include <stdint.h>
#include "ports.h"

void tone(uint32_t freq)
{
  uint32_t div;
  uint8_t  tmp;

  div = 1193180 / freq;

  out(0x43, 0xb6);
  out(0x42, (uint8_t) (div));
  out(0x42, (uint8_t) (div >> 8));

  tmp = in(0x61);
  if(tmp != (tmp | 3)) {
    out(0x61, tmp | 3);
  }
}

void noTone()
{
  uint8_t tmp = in(0x61) & 0xfc;

  out(0x61, tmp);
}
