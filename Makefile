.PHONY: all assemble emulate-i386 emulate-x86_64 write-to-sdb qemu-test-usb-felix-only run clean
BIN=./bin/boot1.bin
ASMS=./source/bootloader/boot1.asm
NASMOPTS=-i./source/lib -i./source/bootloader -f bin

all: assemble

assemble:
	if [ ! -d ./bin ]; then \
		mkdir ./bin; \
	fi; \
	nasm $(NASMOPTS) $(ASMS) -o $(BIN)

emulate-i386:
	qemu-system-i386 -hda $(BIN)

emulate-x86_64:
	qemu-system-x86_64 -hda $(BIN)

write-to-sdb:
	sudo dd if=$(BIN) of=/dev/sdb

qemu-test-usb-felix-only:
	sudo qemu-system-x86_64 -m 512 -enable-kvm -usb -device usb-host,hostbus=2,hostaddr=4

run: assemble emulate-x86_64

clean:
	rm -r ./bin/*
