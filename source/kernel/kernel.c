#include "../drivers/vga.h"
#include "../lib/c/types.h"

//Main kernel entry point
void main() {
	delaySeconds(2);
	clrscr(PURPLE_ON_BLACK);
	println_string("OnyxOS Version 0.0.4");
	println_string("Copyright (c) 2021 Omer Shamai, Yuri Khordal, Felix Janetzki");

}
