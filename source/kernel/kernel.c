#include "timer.h"
#include "sys.h"
#include "vga.h"
#include "util.h"
#include "ISR.h"
#include "keyboard.h"
#include "stdbool.h"
#include "dmm.h"
#include "string.h"
#include "speaker.h"
#include "ports.h"
#include "g_vga.h"
#include "stdint.h"
#include "math.h"

unsigned char cpustring[16];

void prologue()
{

	clrscr();

	print_string("ISRs : ");
	isr_install();
	println_string_color("OK", EMERALD_ON_BLACK);

	print_string("EXINT : ");
	__asm__ volatile("sti");
	println_string_color("OK", EMERALD_ON_BLACK);

	print_string("TIMER (IRQ0) : ");
	init_timer(1);
	delay(500);
	println_string_color("OK", EMERALD_ON_BLACK);

	print_string("KEYBOARD (IRQ1) : ");
	init_keyboard();
	delay(500);
	println_string_color("OK", EMERALD_ON_BLACK);

	print_string("DYNMEM (alloc, malloc, free) : ");
	init_dmm();
	delay(500);
	println_string_color("OK", EMERALD_ON_BLACK);

	get_cpu_vendor_string(cpustring);

	if(extended_cpuid_available() == false) {
		println_string_color("CPUID: FATAL ERR", RED_ON_BLACK);
		delay(3000);
		hang("NO CPUID");
	} else {
		print_string("CPUID : ");
		delay(500);
		println_string_color("OK", EMERALD_ON_BLACK);
	}

		delay(1000);
		clrscr();

		println_string_color("     _/_/                                    _/_/      _/_/_/   ", YELLOW_ON_BLACK);
		println_string_color("  _/    _/  _/_/_/    _/    _/  _/    _/  _/    _/  _/          ", YELLOW_ON_BLACK);
		println_string_color(" _/    _/  _/    _/  _/    _/    _/_/    _/    _/    _/_/       ", YELLOW_ON_BLACK);
		println_string_color("_/    _/  _/    _/  _/    _/  _/    _/  _/    _/        _/      ", YELLOW_ON_BLACK);
		println_string_color(" _/_/    _/    _/    _/_/_/  _/    _/    _/_/    _/_/_/         ", YELLOW_ON_BLACK);
		println_string_color("                        _/                                      ", YELLOW_ON_BLACK);
		println_string_color("                   _/_/                                         ", YELLOW_ON_BLACK);

		beep(2415, 1);

		print_string("OnyxOS (kernel_version x86_64-32_bit-0.1.1) Running on ");
		println_string_color(cpustring, LCYAN_ON_BLACK);
		char *d = (char*) malloc(sizeof(char)*16);
		char *e = (char*) malloc(sizeof(char)*16);
		itos(DYNMEM_SZ, d);
		itos(sizeof(dynmem_node_t), e);
		append(d, 'B');
		append(e, 'B');
		print_string("Total dynamic memory: ");
		print_string_color(d, LCYAN_ON_BLACK);
		println_string_color(" (-16B)", LCYAN_ON_BLACK);
		print_string("Dynamic node size: ");
		println_string_color(e, LCYAN_ON_BLACK);
		println_string("Copyright (c) 2021 Yuri Khordal, Felix Janetzki");
		print_string_color("]> ", LCYAN_ON_BLACK);

	}



//Main kernel entry point
void main(void)
{
		//prologue();
		g_clrscr();
		uint16_t color = (0x0b+0x30);
		ipoint_t points[5] = {
			{10, 10},
			{30,  5},
			{50, 15},
			{20, 70},
			{ 5, 30},
		};


		g_poly(points, 5, color);
		g_rect(70, 20, 90, 70, color);
		g_fill_rect(100, 20, 120, 70, color);
		g_line(100, 100, 200, 130, color);
		// for (size_t i = 100; i < 150; i+=5) {
		// 	g_rect(i, i, 150-i, 150-i, color);
		// }

}
