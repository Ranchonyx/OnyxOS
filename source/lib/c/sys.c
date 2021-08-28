#include "sys.h"
#include "util.h"
#include "sys_strings.h"
#include "vga.h"
#include "ports.h"
#include "dmm.h"

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
//Confirmed
void get_cpu_vendor_string(char dest[])
{
	uint32_t eax, ebx, ecx, edx;
	eax = 0x0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	//EBX;EDX;ECX required

	strcat(dest, register_to_string(ebx));
	strcat(dest, register_to_string(edx));
	strcat(dest, register_to_string(ecx));

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

void hang(char *cause)
{
  set_cursor(COLS_MAX-(strlen(cause) + strlen(SYS_HANG)));
  print_string_color(SYS_HANG, RED_ON_BLACK);
  println_string_color(cause, RED_ON_BLACK);
  set_cursor(0);
  __asm__ volatile("cli; hlt");
}

//Some really unhealthy shit right here
void restart_kernel()
{
  __asm__ volatile("jmp 0x9000");
}

//Dunno what it's for just wanted to implement it have a nice day
uint8_t __cmos__getMemory()
{
  unsigned short total;
  unsigned char low, hi;

  outb(0x70, 0x30);
  low = inb(0x71);
  outb(0x70, 0x31);
  hi = inb(0x71);

  total = low | hi << 8;
  return total;
}

//Run a command defined below
int cmd(char* command)
{
  lower(command);
  print_string_color("EXEC \"", TEAL_ON_BLACK);
  print_string_color(command, TEAL_ON_BLACK);
  println_string_color("\"", TEAL_ON_BLACK);


  if(compare_string(command, "krestart") == 0) {
    println_string("Restarting kernel.");
    delaySeconds(5);
    command[0] = '\0';
    restart_kernel();
    return 0;
  } else if(compare_string(command, "shutdown") == 0) {
    outw(0x604, 0x2000);
    return 0;
  } else if(compare_string(command, "cpuvendor") == 0) {
    char s[16];
    get_cpu_vendor_string(s);
    println_string(s);
    return 0;
  } else if(compare_string(command, "clrscr") == 0) {
    clrscr(WHITE_ON_BLACK);
    return 0;
  } else if(compare_string(command, "help") == 0) {
    println_string("shutdown (qemu)\nkrestart\ncpuvendor\nclrscr\nhelp");
    return 0;
  } else if(compare_string(command, "dynmem") == 0) {
    print_dynmem();
    return 0;
  } else if(compare_string(command, "reboot") == 0) {
    outb(0x64, 0xFE);
    return 0;
  }

  println_string_color("UNKNOWN COMMAND", TEAL_ON_BLACK);

  return 1;
}
