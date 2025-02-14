#ifndef SYS_H
#define SYS_H
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdbool.h>

// typedef struct linked_list_head {
//   struct linked_list_head *prev;
//   struct linked_list_head *next;
// } linked_list_t;



void native_cpuid(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t * edx);
void hang(char *cause);
void *memcpy(void* dest, const void* src, size_t n);
void *memmove (void* dest, const void* src, size_t n);
char *register_to_string(uint32_t reg);
void get_cpu_vendor_string(char dest[]);
void get_cpu_brand_string(char dest[]);
bool extended_cpuid_available();
char **argparse(char *cmd);
int  cmd(char* command);
void delay(uint32_t millis);

#endif /* end of include guard: SYS_H */
