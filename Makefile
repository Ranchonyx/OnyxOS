C_SOURCES = $(wildcard source/kernel/*.c)
HEADERS = $(wildcard source/kernel/*.h)
OBJ_FILES = ${C_SOURCES:.c=.o}

all: sys/sys.bin

source/kernel/kernel.bin: source/lib/asm/kentry.o ${OBJ_FILES}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

source/lib/asm/kentry.o:   source/lib/asm/kentry.asm
	nasm $< -f elf -o $@

source/kernel/vga.o:	  source/kernel/vga.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

source/kernel/ports.o:    source/kernel/ports.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

source/kernel/util.o:    source/kernel/util.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

source/kernel/kernel.o:   source/kernel/kernel.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

source/bootloader/mbr.bin:    source/bootloader/mbr.asm
	nasm $< -f bin -o $@

sys/sys.bin:    source/bootloader/mbr.bin source/kernel/kernel.bin
	cat $^ > $@

run:        sys/sys.bin
	qemu-system-x86_64 -fda $<

clean:
	$(RM) source/bootloader/*.bin source/bootloader/*.o
	$(RM) source/kernel/*.bin source/kernel/*.o
	$(RM) sys/*.bin sys/*.o
