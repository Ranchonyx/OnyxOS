#include "IDT.h"
#include "sys.h"
#include "vga.h"

#define high16(address) (uint16_t)(((address) >> 16) & 0xFFFF)
#define low16(address) (uint16_t)((address) & 0xFFFF)

idt_gate_t idt[256];
idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler)
{
  idt[n].low = low16(handler);
  idt[n].selector = 0x08;
  idt[n].always0 = 0;
  idt[n].flags = 0x8E;
  idt[n].high = high16(handler);
}

void load_idt()
{
  idt_reg.base = (uint32_t) &idt;
  idt_reg.limit = 256 * sizeof(idt_gate_t) - 1;

  __asm__ volatile("lidt (%0)" : : "r" (&idt_reg));
}
