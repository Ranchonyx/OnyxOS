#include "string.h"
#include "dmm.h"


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

int backspace(char s[])
{
  size_t len = strlen(s);
  if(len > 0) {
    s[len - 1] = '\0';
    return 0;
  } else {
    return 1;
  }
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

char* strtok(char* string, const char* delimiter)
{
  static int currentIndex = 0;
  if(!string || !delimiter || string[currentIndex] == '\0') {
    return XNULL;
  }
  char *buf = (char*) malloc(sizeof(char) * 100);
  int i = currentIndex;
  int k = 0;
  int j = 0;

  while (string[i] != '\0') {
    j = 0;
    while (delimiter[j] != '\0') {
      if(string[i] != delimiter[j]) {
        buf[k] = string[i];
      } else {
        goto It;
      }
      j++;
    }
    i++;
    k++;
  }
  It:
  buf[i] = 0;
  currentIndex = i + 1;
  return buf;
}
