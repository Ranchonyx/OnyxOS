#include "vga.h"
#include "util.h"
#include "ports.h"
#include "sys.h"
#include "ISR.h"
#include "keyboard.h"
#include "stdbool.h"
#include "textmode_gfx.h"

bool fastboot = false;

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
	// unsigned char* location = (unsigned char*)0xA0000 + 320 * 10 + 10;
	// *location = GREEN_ON_BLACK;
		prologue();
		line(0, 10, 15, 0, (char)178, YELLOW_ON_BLACK);
}
