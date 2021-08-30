#ifndef TIMER_H
#define TIMER_H
#include "stddef.h"
#include "ISR.h"

static uint32_t ticks = 0;

void timer_callback(registers_t *regs);
void init_timer(uint32_t freq);
uint32_t get_ticks();

#endif /* end of include guard: TIMER_H */
