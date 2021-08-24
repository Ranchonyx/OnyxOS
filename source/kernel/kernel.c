#include "vga.h"
#include "util.h"
#include "ports.h"
#include "sys.h"

void prologue() {
	//#region
	delaySeconds(5);
	clrscr(WHITE_ON_BLACK);
	color_test();
	if(extended_cpuid_available() == false) {
		println_string_color("NO EXTENDED CPUID FUNCTIONS!\n", RED_ON_BLACK);
		delaySeconds(3);
	} else {
		println_string_color("CPUID SUPPPORTS EXTENDED FUNCTIONS!\n", GREEN_ON_BLACK);
	}
	delaySeconds(5);
	clrscr(WHITE_ON_BLACK);

	println_string_color("     _/_/                                    _/_/      _/_/_/   ", YELLOW_ON_BLACK);
	println_string_color("  _/    _/  _/_/_/    _/    _/  _/    _/  _/    _/  _/          ", YELLOW_ON_BLACK);
	println_string_color(" _/    _/  _/    _/  _/    _/    _/_/    _/    _/    _/_/       ", YELLOW_ON_BLACK);
	println_string_color("_/    _/  _/    _/  _/    _/  _/    _/  _/    _/        _/      ", YELLOW_ON_BLACK);
	println_string_color(" _/_/    _/    _/    _/_/_/  _/    _/    _/_/    _/_/_/         ", YELLOW_ON_BLACK);
	println_string_color("                        _/                                      ", YELLOW_ON_BLACK);
	println_string_color("                   _/_/                                         ", YELLOW_ON_BLACK);	//#endregion

	print_string("OnyxOS Version 0.0.6 Running on ");
	println_string_color(/*get_cpu_vendor_string()*/get_cpu_vendor_string(), TEAL_ON_BLACK);

	println_string("Copyright (c) 2021 Omer Shamai, Yuri Khordal, Felix Janetzki");
	println_string("Special thanks to Fast-Nop for continuous help to us assembly-lethargics!");
}
//Main kernel entry point
void main() {
		prologue();
}
