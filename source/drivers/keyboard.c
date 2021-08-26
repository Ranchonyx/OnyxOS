#include "keyboard.h"
#include "ISR.h"
#include "vga.h"
#include "util.h"
#include "ports.h"
#include "sys.h"
#include "string.h"

static char buffer[256];

const char *sc_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6",
                         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
                         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
                         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
                         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
                         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                        '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};


static void keyboard_callback(registers_t *regs)
{
  uint8_t scancode = in(0x60);

    if(scancode > 57) {
      return;
    }
    if(scancode == 0x0E) {
      //print backspace char to keybuf
    } else if(scancode == 0x1C) {
      //Enter
      println_string("");
      cmd(buffer);
      buffer[0] = '\0';
      print_string_color("]> ", TEAL_ON_BLACK);
    } else {
      char chr = sc_ascii[(int) scancode];
      append(buffer, chr);
      char str[2] = {chr, '\0'};
      print_string(str);
    }
}

void init_keyboard()
{
  register_interrupt_handler(IRQ1, keyboard_callback);
}
