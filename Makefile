all: sys/sys.bin

source/kernel/kernel.bin: source/bootloader/kentry.o source/kernel/kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

source/bootloader/kentry.o:   source/bootloader/kentry.asm
	nasm $< -f elf -o $@

source/kernel/kernel.o:   source/kernel/kernel.c
	gcc -m32 -fno-pie -ffreestanding -c $< -o $@

source/bootloader/mbr.bin:    source/bootloader/mbr.asm
	nasm $< -f bin -o $@

sys/sys.bin:    source/bootloader/mbr.bin source/kernel/kernel.bin
	cat $^ > $@

run:        sys/sys.bin
	qemu-system-x86_64 -fda $<

clean:
	$(RM) *.bin *.o *.dis *.img
