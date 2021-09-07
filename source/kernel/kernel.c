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

	g_clrscr();

	g_t_print_string("ISRs : ", 0xf);
	isr_install();
	g_t_print_string("OK\n", 0xa);

	g_t_print_string("EXINT : ", 0xf);
	__asm__ volatile("sti");
	g_t_print_string("OK\n", 0xa);

	g_t_print_string("TIMER (IRQ0) : ", 0xf);
	init_timer(1);
	delay(500);
	g_t_print_string("OK\n", 0xa);

	g_t_print_string("KEYBOARD (IRQ1) : ", 0xf);
	init_keyboard();
	delay(500);
	g_t_print_string("OK\n", 0xa);

	g_t_print_string("DYNMEM (malloc, free) : ", 0xf);
	init_dmm();
	delay(500);
	g_t_print_string("OK\n", 0xa);

	get_cpu_vendor_string(cpustring);

	if(extended_cpuid_available() == false) {
		g_t_print_string("CPUID: FATAL ERR\n", 0x4);
		delay(3000);
		hang("NO CPUID");
	} else {
		g_t_print_string("CPUID : ", 0xf);
		delay(500);
		g_t_print_string("OK\n", 0xa);
	}

		delay(1000);
		clrscr();

		// println_string_color("     _/_/                                    _/_/      _/_/_/   ", YELLOW_ON_BLACK);
		// println_string_color("  _/    _/  _/_/_/    _/    _/  _/    _/  _/    _/  _/          ", YELLOW_ON_BLACK);
		// println_string_color(" _/    _/  _/    _/  _/    _/    _/_/    _/    _/    _/_/       ", YELLOW_ON_BLACK);
		// println_string_color("_/    _/  _/    _/  _/    _/  _/    _/  _/    _/        _/      ", YELLOW_ON_BLACK);
		// println_string_color(" _/_/    _/    _/    _/_/_/  _/    _/    _/_/    _/_/_/         ", YELLOW_ON_BLACK);
		// println_string_color("                        _/                                      ", YELLOW_ON_BLACK);
		// println_string_color("                   _/_/                                         ", YELLOW_ON_BLACK);

		beep(2415, 1);

		g_t_print_string("OnyxOS Running on ", 0xf);
		g_t_print_string(cpustring, 0x3);
    g_t_print_string("\n",0x0);
		char *d = (char*) malloc(sizeof(char)*16);
		char *e = (char*) malloc(sizeof(char)*16);
		itos(DYNMEM_SZ, d);
		itos(sizeof(dynmem_node_t), e);
		append(d, 'B');
		append(e, 'B');
		g_t_print_string("Total dynamic memory: ", 0xf);
		print_string_color(d, 0x3);
		g_t_print_string(" (-16B)\n", 0x3);
		g_t_print_string("Dynamic node size: ", 0xf);
		g_t_print_string(e, 0x3);
    g_t_print_string("\n",0x0);
		g_t_print_string("Copyright (c) 2021 Yuri Khordal, Felix Janetzki\n",0xf);
		g_t_print_string("]> ", 0x3);
	}

//Main kernel entry point
void main(void)
{
  prologue();
  beep(2415, 1);


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
    //
    //
    // char *s = "circle, 10, 10, 10, 0x4";
    // char delm[] = ",";
    // char *str = strtok(s, delm);
    // while(str) {
    //   g_t_print_string(str, 0xf);
    //   g_t_print_string("\n", 0x0);
    //   str = strtok(s, delm);
    // }


}
