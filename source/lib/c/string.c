#include "string.h"


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
