#include "string.h"

void* memcpy(void* dest, const void* src, size_t n){
  char* cdest = (char*)dest;
  const char* csrc = (const char*)src;
  for (size_t i = 0; i < n; i++) cdest[i] = csrc[i];
  return dest;
}

void* memmove (void* dest, const void* src, size_t n){
  if (src == dest) return dest;

  char* cdest = (char*)dest;
  const char* csrc = (const char*)src;

  if (cdest > csrc) while (n--) cdest[n] = csrc[n];
  else for (size_t i = 0; i < n; i++) cdest[i] = csrc[i];

  return dest;
}

size_t strlen(const char* str){
  size_t len = 0;
  while (*(str + len)) len++;
  return len;
}

//From linux kernel
char* strcat(char* dest, char* src)
{
  char *rdest = dest;

while (*dest)
  dest++;
while (*dest++ = *src++)
  ;
return rdest;
}
