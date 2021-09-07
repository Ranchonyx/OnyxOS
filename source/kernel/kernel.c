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
#include "complex.h"

unsigned char cpustring[16];

void plotMandel(double _min_re, double _max_re, double _min_im, int max_iter, double scale) {

  double min_re = scale * _min_re;
  double max_re = scale * _max_re;
  double min_im = scale * _min_im;
  double max_im = min_im+(max_re-min_re) * RES_VERTICAL/RES_HORIZONTAL;
  double re_fac = (max_re-min_re)/(RES_HORIZONTAL-1);
  double im_fac = (max_im-min_im)/(RES_VERTICAL-1);
  uint32_t color = 0x000000;
  //uint16_t color = 0x0000;
  //uint8_t color = 0x00;
  for(int y = 0; y < RES_VERTICAL; y++) {

    double c_im = max_im - y * im_fac;
    for(int x = 1; x < RES_HORIZONTAL; x++) {

      double c_re = min_re + x*re_fac;
      double z_re = c_re;
      double z_im = c_im;
      bool inside = true;

      for(int iter = 1; iter < max_iter; iter++) {

        color = UINT32_MAX * sin(iter);

        double z_re2 = z_re * z_re;
        double z_im2 = z_im * z_im;

        if(z_re2 + z_im2 > 4) {
          inside = false;
          break;
        }

        z_im = 2 * z_re * z_im + c_im;
        z_re = z_re2 - z_im2 + c_re;
        if(inside) {
          g_set_pixel(x, y, color);
        }

      }
    }
  }
}

void plotJulia(int max_iter) {
  double min_re = -2.0;
  double max_re = 1.0;
  double min_im = -1.2;
  double max_im = min_im+(max_re-min_re) * RES_VERTICAL/RES_HORIZONTAL;
  double re_fac = (max_re-min_re)/(RES_HORIZONTAL-1);
  double im_fac = (max_im-min_im)/(RES_VERTICAL-1);


  for(int y = 0; y < RES_VERTICAL; y++) {

    double c_im = max_im - y * im_fac;
    for(int x = 1; x < RES_HORIZONTAL; x++) {

      double c_re = min_re + x*re_fac;
      double z_re = c_re;
      double z_im = c_im;
      bool inside = true;

      for(int iter = 1; iter < max_iter; iter++) {
        double z_re2 = z_re * z_re;
        double z_im2 = z_im * z_im;

        if(z_re2 + z_im2 > 4) {
          inside = false;
          break;
        }
        z_im = 2 * z_re * z_im + c_im;
        z_re = z_re2 - z_im2 + (-0.8+0.156);
        if(inside) {
          g_set_pixel(x, y, iter);
        }
      }
    }
  }
}

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
  init_dmm();
  init_vga();
  isr_install();
	__asm__ volatile("sti");
	init_timer(1);
  init_keyboard();
  g_clrscr();

  g_print_string("]>", 0x3, 0x0);

		// uint16_t color = (0x0b+0x30);
		// ipoint_t points[5] = {
		// 	{10, 10},
		// 	{30,  5},
		// 	{50, 15},
		// 	{20, 70},
		// 	{ 5, 30},
		// };
    //
    //
		// g_poly(points, 5, color);
		// g_rect(70, 20, 90, 70, color);
		// g_fill_rect(100, 20, 120, 70, color);
		// g_line(100, 100, 200, 130, color);
		// g_circle(100, 100, 45, color);




		// for (size_t i = 100; i < 150; i+=5) {
		// 	g_rect(i, i, 150-i, 150-i, color);
		// }

		// for(int x0 = 0; x0 < RES_HORIZONTAL; x0++) {
		// 	g_set_pixel(x0, 0, UINT32_MAX * pow(x0,2));
		// }
    //
		// for(int y0 = 0; y0 < RES_VERTICAL; y0++) {
		// 	g_set_pixel(0, y0, UINT32_MAX * tan(y0));
		// }

    // for(int i = 0; i < 500; i++) {
    //   plotMandel(-1.0, 1.0, -2, i, 0.5);
    //   //plotMandel(-2.0, 1.0, -1.2, i, 1);
    //   delay(100);
    // }
    // double min_re = -2.0;
    // double max_re = 1.0;
    // double min_im = -1.2;

    // ipoint_t schande[RES_TOTAL];
    // for(int x = 1; x < RES_HORIZONTAL-10; x+=2) {
    //   for(int y = 1; y < RES_VERTICAL-10; y+=2) {
    //     // col = (g_get_color(x - 1, y) + g_get_color(x, y - 1));
    //    size_t // col = (col / 2);
    //     col = pow(2*(x+y), 3);
    //     g_fill_rect(x, y, x+10, y+10);
    //     }
    // }
    //


    // char str[] = "Hello, Yeeter";
    // char* ptr = strtok(str, "y");
    // char* arr[2];
    // int i = 0;
    // while(ptr != 0) {
    //   arr[i] = ptr;
    //   ptr = strtok(XNULL, ",");
    // }
    //
    // for (int i = 0; i < 3; i++) {
    //   g_print_string("Value: ", 0xf, 0x0);
    //   g_print_string(arr[i], 0xf, 0x0);
    //   g_print_string("\n", 0x0, 0x0);
    // }

    char *s = "circle, 10, 10, 10, 0x4";
    char delm[] = ",";
    char *str = strtok(s, delm);
    while(str) {
      g_print_string(str, 0xf, 0x0);
      g_print_string("\n", 0x0, 0x0);
      str = strtok(s, delm);
    }


}
