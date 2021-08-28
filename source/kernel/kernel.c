#include "vga.h"
#include "util.h"
#include "sys.h"
#include "ISR.h"
#include "keyboard.h"
#include "stdbool.h"
#include "dmm.h"
#include "string.h"

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
		delaySeconds(1);
		println_string_color("OK", EMERALD_ON_BLACK);
		if(extended_cpuid_available() == false) {
			println_string_color("CPUID: FATAL ERR", RED_ON_BLACK);
			delaySeconds(3);
			hang("NO CPUID");
		} else {
			print_string("CPUID : ");
			delaySeconds(1);
			println_string_color("OK", EMERALD_ON_BLACK);
		}
		print_string("ISRs : ");
		isr_install();
		delaySeconds(1);
		println_string_color("OK", EMERALD_ON_BLACK);

		print_string("EXINT : ");
		__asm__ volatile("sti");
		delaySeconds(1);
		println_string_color("OK", EMERALD_ON_BLACK);

		print_string("DYNMEM (alloc, malloc, free) : ");
		init_dmm();
		delaySeconds(1);
		println_string_color("OK", EMERALD_ON_BLACK);

		print_string("KEYBOARD (IRQ1) : ");
		init_keyboard();
		delaySeconds(1);
		println_string_color("OK", EMERALD_ON_BLACK);

		delaySeconds(2);
		clrscr(WHITE_ON_BLACK);

		println_string_color("     _/_/                                    _/_/      _/_/_/   ", YELLOW_ON_BLACK);
		println_string_color("  _/    _/  _/_/_/    _/    _/  _/    _/  _/    _/  _/          ", YELLOW_ON_BLACK);
		println_string_color(" _/    _/  _/    _/  _/    _/    _/_/    _/    _/    _/_/       ", YELLOW_ON_BLACK);
		println_string_color("_/    _/  _/    _/  _/    _/  _/    _/  _/    _/        _/      ", YELLOW_ON_BLACK);
		println_string_color(" _/_/    _/    _/    _/_/_/  _/    _/    _/_/    _/_/_/         ", YELLOW_ON_BLACK);
		println_string_color("                        _/                                      ", YELLOW_ON_BLACK);
		println_string_color("                   _/_/                                         ", YELLOW_ON_BLACK);
		//#endregion


		print_string("OnyxOS (kernel_version x86_64-32_bit-0.1.1) Running on ");
		println_string_color(cpustring, LCYAN_ON_BLACK);
		char d[256];
		char e[256];
		itos(DYNMEM_SZ, d);
		itos(sizeof(dynmem_node_t), e);
		append(d, 'B');
		append(e, 'B');
		print_string("Total dynamic memory: ");
		println_string_color(d, LCYAN_ON_BLACK);
		print_string("Dynamic node size: ");
		println_string_color(e, LCYAN_ON_BLACK);
		println_string("Copyright (c) 2021 Yuri Khordal, Felix Janetzki");
	}

	print_string_color("]> ", LCYAN_ON_BLACK);
}

//Main kernel entry point
void main() {
		prologue();
}
