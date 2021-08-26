#ifndef IDT_H
#define IDT_H
#include "stdint.h"

typedef struct {
  uint16_t  low;
  uint16_t  selector;
  uint8_t   always0;
  uint8_t   flags;
  uint16_t  high;
} __attribute__((packed)) idt_gate_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_register_t;

static char *exception_messages[] = {
  "Division By Zero",
  "Debug",
  "Non Maskable Interrupt",
  "Breakpoint",
  "Into Detected Overflow",
  "Out of Bounds",
  "Invalid Opcode",
  "No Coprocessor",

  "Double Fault",
  "Coprocessor Segment Overrun",
  "Bad TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page Fault",
  "Unknown Interrupt",

  "Coprocessor Fault",
  "Alignment Check",
  "Machine Check",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"
};


void set_idt_gate(int n, uint32_t handler);
void load_idt();

#endif /* end of include guard: IDT_H */
