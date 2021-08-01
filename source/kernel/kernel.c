#include "vga.h"
#include "util.h"

//Main kernel entry point
void main() {
	//#region
	delaySeconds(1);
	clrscr(LGREY_ON_BLACK);
	color_test();
	delaySeconds(1);
	clrscr(LGREY_ON_BLACK);
	printLogo();
	//#endregion

	print_string("OnyxOS Version 0.0.6 Running on ");
	println_string_color(get_cpu_vendor_string(), TEAL_ON_BLACK);
	println_string("Copyright (c) 2021 Omer Shamai, Yuri Khordal, Felix Janetzki");
	println_string("Special thanks to Fast-Nop for continuous help to us assembly-lethargics!");


}
