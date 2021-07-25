C_SOURCES = $(wildcard source/kernel/*.c source/cpudata/*.c source/lib/c/*.c source/drivers/*.c)
HEADERS = $(wildcard source/kernel/*.h source/cpudata/*.h source/lib/c/*.h source/drivers/*.h)
OBJ_FILES = ${C_SOURCES:.c=.o}

all: run

source/kernel/kernel.bin: source/lib/asm/kentry.o ${OBJ_FILES}
	ld -m elf_i386 -o $@ -Ttext 0x9000 $^ --oformat binary

source/lib/asm/kentry.o:   source/lib/asm/kentry.asm
	nasm $< -f elf -o $@

source/bootloader/mbr.bin:    source/bootloader/mbr.asm
	nasm $< -f bin -o $@

sys/sys.bin:    source/bootloader/mbr.bin source/kernel/kernel.bin
	cat $^ > $@

run:        		sys/sys.bin
	qemu-system-x86_64 -soundhw pcspk -hda $<

%.o: %.c ${HEADERS}
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

%.o:   %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	$(RM) source/bootloader/*.bin source/bootloader/*.o
	$(RM) source/kernel/*.bin source/kernel/*.o
	$(RM) sys/*.bin sys/*.o
	$(RM) source/cpudata/*b.in source/cpudata/*.o
