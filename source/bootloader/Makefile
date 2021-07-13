.PHONY: run clean
obj-m+=boot1.bin

assemble:
	nasm -f bin ./boot1.asm -o boot1.bin

emulate-i386:
	qemu-system-i386 -hda ./boot1.bin

emulate-x86_64:
	qemu-system-x86_64 -hda ./boot1.bin

write-to-sdb:
	sudo dd if=./boot1.bin of=/dev/sdb

qemu-test-usb-felix-only:
	sudo qemu-system-x86_64 -m 512 -enable-kvm -usb -device usb-host,hostbus=2,hostaddr=4

clean:
	rm -rf ./*.bin
