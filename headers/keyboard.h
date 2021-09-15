#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "ISR.h"


void init_keyboard();
static void keyboard_callback(registers_t *regs);

#endif /* end of include guard: KEYBOARD_H */
