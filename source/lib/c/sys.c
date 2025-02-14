#include "timer.h"
#include "sys.h"
#include "util.h"
#include "sys_strings.h"
#include "g_vga.h"
#include "ports.h"
#include "dmm.h"
#include "util.h"
#include "colors.h"

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
char *register_to_string(uint32_t reg)
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

void get_cpu_brand_string(char dest[])
{
  char *buf = (char*) malloc(sizeof(char) * (16*3));
  uint32_t ebx, ecx, edx;
  uint32_t eax = 0x80000002;
  native_cpuid(&eax, &ebx, &ecx, &edx);
  strcat(buf, register_to_string(eax));
  strcat(buf, register_to_string(ebx));
  strcat(buf, register_to_string(ecx));
  strcat(buf, register_to_string(edx));
  eax = 0x80000003;
  native_cpuid(&eax, &ebx, &ecx, &edx);
  strcat(buf, register_to_string(eax));
  strcat(buf, register_to_string(ebx));
  strcat(buf, register_to_string(ecx));
  strcat(buf, register_to_string(edx));
  eax = 0x80000004;
  native_cpuid(&eax, &ebx, &ecx, &edx);
  strcat(buf, register_to_string(eax));
  strcat(buf, register_to_string(ebx));
  strcat(buf, register_to_string(ecx));
  strcat(buf, register_to_string(edx));
  memcpy(dest, buf, strlen(buf)+1);
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

char **argparse(char *cmd)
{
  char result[strlen(cmd)];
  char delm[] = ",";
  char *str = strtok(cmd, delm);
  int i = 0;
  while(str) {
    result[i] = str;
    str = strtok(str, delm);
    i++;
  }
  return result;
}

void hang(char *cause)
{
  // set_cursor(COLS_MAX-(strlen(cause) + strlen(SYS_HANG)));
  _cursor.y = RES_VERTICAL-16;
  _cursor.x = 0;
  g_t_print_string(SYS_HANG, 0x4);
  g_t_print_string(cause, 0x4);
  __asm__ volatile("cli; hlt");
}

void delay(uint32_t millis) {
	uint32_t tgt = get_ticks()+(millis / 10);;
	while(get_ticks() <= tgt) {

	}
	return;
}

//Run a command defined below
int cmd(char* command)
{
  lower(command);
  g_t_print_string("EXEC \"", OS_INFO);
  g_t_print_string(command, OS_INFO);
  g_t_print_string("\"\n", OS_INFO);


  if(compare_string(command, "shutdown") == 0) {
    outw(0x604, 0x2000);
    return 0;
  } else if(compare_string(command, "cpuvendor") == 0) {
    unsigned char s[16];
    get_cpu_vendor_string(s);
    g_t_print_string(s, 0xf);
    g_t_print_string("\n", 0x0);
    return 0;
  } else if(compare_string(command, "clrscr") == 0) {
    g_clrscr();
    return 0;
  } else if(compare_string(command, "help") == 0) {
    g_t_print_string("shutdown (qemu)\nreboot\ncpuvendor\nclrscr\nhelp\ndynmen\nticks\n", 0xf);
    return 0;
  } else if(compare_string(command, "dynmem") == 0) {
    print_dynmem();
    return 0;
  } else if(compare_string(command, "reboot") == 0) {
    outb(0x64, 0xFE);
    return 0;
  } else if(compare_string(command, "ticks") == 0) {
    uint32_t a = get_ticks();
    char buf[32];
    itos(a, buf);
    g_t_print_string(buf, 0xf);
    g_t_print_string("\n",0x0);
    return 0;
  }

  return 1;
}
