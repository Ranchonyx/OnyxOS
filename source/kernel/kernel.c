#include "vga.h"
#include "util.h"
#include "ports.h"
//Main kernel entry point
void main() {
	//#region
	delaySeconds(5);
	clrscr(WHITE_ON_BLACK);
	color_test();
	if(extended_cpuid_available() == false) {
		println_string_color("\nNO EXTENDED CPUID FUNCTIONS!", RED_ON_BLACK);
		delaySeconds(3);
		hang();
	} else {
		println_string_color("\nCPUID SUPPPORTS EXTENDED FUNCTIONS!", GREEN_ON_BLACK);
	}
	delaySeconds(5);
	clrscr(WHITE_ON_BLACK);

	printLogo();
	//#endregion

	print_string("OnyxOS Version 0.0.6 Running on ");
	println_string_color(get_cpu_vendor_string(), TEAL_ON_BLACK);

	println_string("Copyright (c) 2021 Omer Shamai, Yuri Khordal, Felix Janetzki");
	println_string("Special thanks to Fast-Nop for continuous help to us assembly-lethargics!");

}
