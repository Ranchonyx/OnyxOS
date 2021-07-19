//Main entry point for our "kernel-thing"
void hang() {
  for(;;);
}

unsigned char in(unsigned short _prt) {
  unsigned char result;
  __asm__("in %%dx, %%al" : "=a" (result) : "d" (_prt));
  return result;
}

void out(unsigned short _prt, unsigned char _dat) {
  __asm__("out %%al, %%dx" :: "a" (_dat), "d" (_prt));
}

// Video.c
// Basic graphical functions

void clrsrc() {
  unsigned char *vidmem = (unsigned char *) 0xB8000;

  const long size = 80*25;
  long loop;

  for(loop = 0; loop < size; loop++) {
    *vidmem++ = 0;
    *vidmem++ = 0xF;

    out(0x3D4, 14);
    out(0x3D5, 0);
    out(0x3D5, 15);
    out(0x3D5, 0);
  }
}

void print(const char* _message) {
  unsigned char *vidmem = (unsigned char *) 0xB8000;
  unsigned short offset;
  unsigned long i;

  out(0x3D4, 14);
  offset = in(0x3D5) << 8;
  out(0x3D4, 15);
  offset |= in(0x3D5);

  vidmem += offset*2;

  i = 0;
  while(_message[i] != 0) {
    *vidmem = _message[i++];
    vidmem += 2;
  }


  offset += i;
  out(0x3D5, (unsigned char)(offset));
  out(0x3D4, 14);
  out(0x3D5, (unsigned char)(offset >> 8));
}

void main() {
  char* vidmem = (char*) 0xb8000;
  *vidmem = 'X';
}
