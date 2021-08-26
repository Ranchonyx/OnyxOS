#include "string.h"


size_t strlen(const char* str)
{
  size_t len = 0;
  while (*(str + len)) len++;
  return len;
}

void append(char s[], char c)
{
  size_t len = strlen(s);
  s[len] = c;
  s[len+1] = '\0';
}

void lower(char s[])
{
  size_t len = strlen(s);
  for(int i = 0; i < len; i++) {
    if(s[i] >= 'A' && s[i] <= 'Z') {
      s[i] = s[i]+32;
    }
  }
}

int compare_string(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
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
