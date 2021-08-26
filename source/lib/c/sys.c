#include "sys.h"
#include "util.h"
#include "sys_strings.h"
#include "vga.h"
#include "ports.h"
//#define ALLOC_HEADER_SZ offsetof(alloc_node_t, block)

//Linux Kernel implementation
inline void native_cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
        /* ecx is often an input as well as an output. */
        asm volatile("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}

//Special thanks to Fast-Nop for the char extraction help and patience with me
char *register_to_string(unsigned reg)
{
	char regtext[4];
	char* regtext_ptr = regtext;
	char c1 = (char) (reg >> 24);
	char c2 = (char) ((reg >> 16) & 0xFF);
	char c3 = (char) ((reg >> 8) & 0xFF);
	char c4 = (char) reg;

	regtext[0] = c1;
	regtext[1] = c2;
	regtext[2] = c3;
	regtext[3] = c4;
	regtext[4] = '\0';


	reverse(regtext);
	return regtext_ptr;
}

//Returns the CPU vendor string, glaube ich
char *get_cpu_vendor_string()
{
  asm volatile("pusha");
	uint32_t eax, ebx, ecx, edx;
	eax = 0x0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	//EBX;EDX;ECX required
	char* output = "";
	strcat(output, register_to_string(ebx));
	strcat(output, register_to_string(edx));
	strcat(output, register_to_string(ecx));

  asm volatile("popa");
	return output;

}

void* memcpy(void* dest, const void* src, size_t n)
{
  char* cdest = (char*)dest;
  const char* csrc = (const char*)src;
  for (size_t i = 0; i < n; i++) cdest[i] = csrc[i];
  return dest;
}

void* memmove (void* dest, const void* src, size_t n)
{
  if (src == dest) return dest;

  char* cdest = (char*)dest;
  const char* csrc = (const char*)src;

  if (cdest > csrc) while (n--) cdest[n] = csrc[n];
  else for (size_t i = 0; i < n; i++) cdest[i] = csrc[i];

  return dest;
}

bool extended_cpuid_available()
{
	uint32_t eax, ebx, ecx, edx;
	eax = 0x80000000;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	if(eax == 0) {
		return false;
	} else {
		return true;
	}
	return false;
}

void hang()
{
  set_cursor(0);
  println_string_color(SYS_HANG, RED_ON_BLACK);

  __asm__ volatile("hlt");
}

void restart_kernel()
{
  __asm__ volatile("jmp 0x9000");
}

uint8_t __cmos__getMemory()
{
  unsigned short total;
  unsigned char low, hi;

  out(0x70, 0x30);
  low = in(0x71);
  out(0x70, 0x31);
  hi = in(0x71);

  total = low | hi << 8;
  return total;
}

int cmd(char* command)
{
  lower(command);
  print_string_color("EXEC \"", TEAL_ON_BLACK);
  print_string_color(command, TEAL_ON_BLACK);
  println_string_color("\"", TEAL_ON_BLACK);

  if(compare_string(command, "yah") == 0) {
    println_string("YEET");
    return 0;
  } else if(compare_string(command, "krestart") == 0) {
    println_string("Restarting kernel.");
    delaySeconds(5);
    command[0] = '\0';
    restart_kernel();
    return 0;
  }

  println_string_color("UNKNOWN COMMAND", TEAL_ON_BLACK);

  return 1;
}
