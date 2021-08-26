#include "vga.h"
#include "util.h"
#include "ports.h"
#include "sys.h"
#include "ISR.h"
#include "keyboard.h"

void prologue() {
	//#region
	delaySeconds(5);
	clrscr(WHITE_ON_BLACK);
	color_test();
	if(extended_cpuid_available() == false) {
		println_string_color("\nCPUID: ERR", RED_ON_BLACK);
		delaySeconds(3);
		hang();
	} else {
		print_string("\nCPUID : ");
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
	delaySeconds(5);
	println_string_color("OK", EMERALD_ON_BLACK);

	delaySeconds(10);
	clrscr(WHITE_ON_BLACK);

	println_string_color("     _/_/                                    _/_/      _/_/_/   ", YELLOW_ON_BLACK);
	println_string_color("  _/    _/  _/_/_/    _/    _/  _/    _/  _/    _/  _/          ", YELLOW_ON_BLACK);
	println_string_color(" _/    _/  _/    _/  _/    _/    _/_/    _/    _/    _/_/       ", YELLOW_ON_BLACK);
	println_string_color("_/    _/  _/    _/  _/    _/  _/    _/  _/    _/        _/      ", YELLOW_ON_BLACK);
	println_string_color(" _/_/    _/    _/    _/_/_/  _/    _/    _/_/    _/_/_/         ", YELLOW_ON_BLACK);
	println_string_color("                        _/                                      ", YELLOW_ON_BLACK);
	println_string_color("                   _/_/                                         ", YELLOW_ON_BLACK);
	//#endregion

	print_string("OnyxOS Version 0.0.8 Running on ");
	//println_string_color(/*get_cpu_vendor_string()*/get_cpu_vendor_string(), TEAL_ON_BLACK);

	println_string("Copyright (c) 2021 Yuri Khordal, Felix Janetzki");
	println_string("Special thanks to Fast-Nop for continuous help to us assembly-lethargics!");
	print_string_color("]> ", TEAL_ON_BLACK);

}

//Main kernel entry point
void main() {
		prologue();
}
