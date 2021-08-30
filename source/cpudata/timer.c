#include "timer.h"
#include "vga.h"
#include "ports.h"
#include "ISR.h"


void timer_callback(registers_t *regs)
{
  ticks++;
}

uint32_t get_ticks()
{
  return ticks;
}

void init_timer(uint32_t freq)
{
  register_interrupt_handler(IRQ0, timer_callback);

  uint32_t d = 1193182 / freq;
  uint8_t low = (uint8_t)(d & 0xFF);
  uint8_t high = (uint8_t)((d >> 8) & 0xFF);

  outb(0x43, 0x36);
  outb(0x40, low);
  outb(0x40, high);
}
