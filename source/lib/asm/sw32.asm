[bits 16]
sw32:
	cli
	lgdt [gdt_desc]
	mov eax, cr0
	or eax,  0x1
	mov cr0, eax
	jmp CODE_SEG:init32

[bits 32]
init32:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BEGIN_32_BIT
