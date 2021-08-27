#include "vga.h"
#include "util.h"
#include "ports.h"
#include "sys.h"
#include "ISR.h"
#include "keyboard.h"
#include "stdbool.h"

bool fastboot = true;

void prologue() {

	if(!fastboot) {
		delaySeconds(5);
		char cpustring[12];
		get_cpu_vendor_string(cpustring);

		//#region
		clrscr(WHITE_ON_BLACK);
		color_test();
		print_string("\nVGA : ");
		delaySeconds(3);
		println_string_color("OK", EMERALD_ON_BLACK);
		if(extended_cpuid_available() == false) {
			println_string_color("CPUID: ERR", RED_ON_BLACK);
			delaySeconds(3);
			hang("NO CPUID");
		} else {
			print_string("CPUID : ");
			delaySeconds(3);
			println_string_color("OK", EMERALD_ON_BLACK);
		}
		print_string("ISRs : ");
		isr_install();
		delaySeconds(3);
		println_string_color("OK", EMERALD_ON_BLACK);

		print_string("EXINT : ");
		__asm__ volatile("sti");
		delaySeconds(3);
		println_string_color("OK", EMERALD_ON_BLACK);


		print_string("KEYBOARD (IRQ1) : ");
		init_keyboard();
		delaySeconds(3);
		println_string_color("OK", EMERALD_ON_BLACK);

		delaySeconds(5);
		clrscr(WHITE_ON_BLACK);

		println_string_color("     _/_/                                    _/_/      _/_/_/   ", YELLOW_ON_BLACK);
		println_string_color("  _/    _/  _/_/_/    _/    _/  _/    _/  _/    _/  _/          ", YELLOW_ON_BLACK);
		println_string_color(" _/    _/  _/    _/  _/    _/    _/_/    _/    _/    _/_/       ", YELLOW_ON_BLACK);
		println_string_color("_/    _/  _/    _/  _/    _/  _/    _/  _/    _/        _/      ", YELLOW_ON_BLACK);
		println_string_color(" _/_/    _/    _/    _/_/_/  _/    _/    _/_/    _/_/_/         ", YELLOW_ON_BLACK);
		println_string_color("                        _/                                      ", YELLOW_ON_BLACK);
		println_string_color("                   _/_/                                         ", YELLOW_ON_BLACK);
		//#endregion


		print_string("OnyxOS (kernel_version x86_64-32_bit-0.1.0) Running on ");
		println_string_color(cpustring, TEAL_ON_BLACK);
		println_string("Copyright (c) 2021 Yuri Khordal, Felix Janetzki");
		println_string("Now with interrupts and keyboard input!");
	}

	clrscr(WHITE_ON_BLACK);
	print_string_color("]> ", TEAL_ON_BLACK);
}

//Main kernel entry point
void main() {
		prologue();
			unsigned char fb[VIDMEM_SIZE];
			unsigned char *vidmem = (unsigned char *) VIDMEM_ADDR;

			vidmem[0] = '#';
			vidmem[1] = 0xf1;
			vidmem[VIDMEM_SIZE-1] = '#';
			vidmem[VIDMEM_SIZE] = 0xf1;

			memcpy(fb, vidmem, VIDMEM_SIZE);

			int x = 5;
			int y = 2;
			fb[(x*2) + (COLS_MAX * y * 2)] = 'X';
			fb[(x*2) + (COLS_MAX * y * 2) + 1] = 0xf1;


			memcpy(vidmem, fb, VIDMEM_SIZE);

}
