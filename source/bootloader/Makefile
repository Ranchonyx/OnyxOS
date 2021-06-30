.PHONY: run clean
boot1.bin: boot1.asm
    nasm -f bin ./boot1.asm -o ./boot1.bin

run: boot1.bin
    qemu-system-i386.exe -fda ./boot1.bin

clean:
    rm -rf ./*.bin
