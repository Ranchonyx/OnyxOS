C_SOURCES := $(shell find source -name *.c)
HEADERS := $(shell find source -name *.h)
OBJ_FILES := $(patsubst source/%.c, obj/%.o, $(C_SOURCES) )
GCC_FLAGS := -Iheaders -m32 -fno-pie -ffreestanding
NASM_FLAGS := -Isource/lib/asm

#The directory structure of bin/ and obj/
ASM_FILES := $(shell find source -name *.asm)
OBJ_DIR := $(patsubst source/%.asm, obj/%.o, $(ASM_FILES))
OBJ_DIR := $(shell dirname $(OBJ_FILES) $(OBJ_DIR))
#BIN_DIR := $(shell dirname $(patsubst source/%.asm, bin/%.bin, $(ASM_FILES)))
BIN_DIR := bin/bootloader bin/kernel

.PHONY: all clean init

all: init run

bin/kernel/kernel.bin:  obj/lib/asm/kentry.o ${OBJ_FILES}
	ld -m elf_i386 -o $@ -Ttext 0x9000 $^ --oformat binary

obj/lib/asm/kentry.o:   source/lib/asm/kentry.asm
	nasm $(NASM_FLAGS) $< -f elf -o $@

bin/bootloader/mbr.bin: source/bootloader/mbr.asm
	nasm $(NASM_FLAGS) $< -f bin -o $@

bin/sys.bin:            bin/bootloader/mbr.bin bin/kernel/kernel.bin
	cat $^ > $@

run:                    bin/sys.bin
	qemu-system-x86_64 -soundhw pcspk -hda $<

obj/%.o: source/%.c ${HEADERS}
	gcc $(GCC_FLAGS) -c $< -o $@

obj/%.o: source/%.asm
	nasm $(NASM_FLAGS) $< -f elf -o $@

bin/%.bin: source/%.asm
	nasm $(NASM_FLAGS) $< -f bin -o $@

init:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

test:
	echo $(OBJ_FILES)
	echo $(BIN_FILES)

clean:
	$(RM) -r bin/*
	$(RM) -r obj/*
