.PHONY: run clean
obj-m+=boot1.bin

assemble:
	nasm -f bin ./boot1.asm -o boot1.bin

emulate-i386:
	qemu-system-i386 -fda ./boot1.bin

clean:
	rm -rf ./*.bin
