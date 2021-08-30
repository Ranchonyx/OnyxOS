#include "speaker.h"
#include "ports.h"
#include "util.h"

void beep(uint32_t freqdiv, uint32_t del)
{

  uint32_t d = 1193180 / freqdiv;
  uint8_t low = (uint8_t)(d & 0xFF);
  uint8_t high = (uint8_t)((d >> 8) & 0xFF);

  outb(0x43, 0xb6);
  outb(0x42, low);
  outb(0x42, high);

  uint8_t val = inb(0x61);
  val = val | 3;
  outb(0x61, val);

  delay(del);
  val = inb(0x61);
  val = val & 252;
  outb(0x61, val);
}
