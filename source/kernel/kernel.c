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

	println_string("OnyxOS Version 0.0.4");
	println_string("Copyright (c) 2021 Omer Shamai, Yuri Khordal, Felix Janetzki");

	int infotype = 0;
	int a, b, c, d;
	char* _infotype, ebx, eax, ecx, edx;
	asm volatile("cpuid"
					: "=a" (a), "=b" (b), "=c" (c), "=d" (d)   // The output variables. EAX -> a and vice versa.
					: "0" (infotype));                         // Put the infotype into EAX.

							itos(infotype, _infotype);
							itos(a, ebx);
							itos(b, eax);
							itos(c, ecx);
							itos(d, edx);
	println_string(_infotype);
	println_string(ebx);
	println_string(edx);
	println_string(ecx);
	println_string(eax);

}
