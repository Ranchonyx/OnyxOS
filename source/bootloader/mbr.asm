;16 Bit Real Mode
[bits 16]
;Set Origin to 0x7c00
[org  0x7c00]

;Kernel Entry Point Offset is 0x1000 (See Makefile [ld task])
KOFFSET equ 0x9000

;Load 64 Sectors of Disk into RAM
SECTORS_TO_LOAD equ 64
;Bootloader entry point at 0x7c00
global _start
_start:
jmp loader_entry

;Define Hardcoded Strings
asciitest     db "[OnyxOS] Printing available ASCII Characters",0
done          db "[OnyxOS] Done"                               ,0
launch        db "[OnyxOS] Starting Bootloader"                ,0
protmode_msg  db "[OnyxOS] Moving to 32-Bit Protected Mode"    ,0
error	        db "Disk Error / Load Error / No CPUID"			     ,0

;Reserve Boot Drive
BOOT_DRIVE    db 0

;Include the retard standard assembly library
%include "rstdlib.asm"

;Bootloader Code Starts here
loader_entry:

;Save boot drive from DL into BOOT_DRIVE
mov [BOOT_DRIVE], dl

mov bl, 1
mov si, launch
call PrintString

mov si, asciitest
call PrintString

call PrintNewline

mov bl, 0
call PrintAsciiCharacters

call PrintNewline

mov bl, 1
mov si, done
call PrintString

mov si, protmode_msg
call PrintString

; jmp $


;Initialize Stack base at 0x10500, Initialize Stack Pointer at Base for now
mov bp, 0x10500
mov sp, bp

;Load Kernel
call lkernel

;Switch to 32 Bit Protected Mode

call sw32

;Hang
jmp $

%include "disk.asm"
%include "gdt.asm"
%include "sw32.asm"
;%include "print32.asm"

[bits 16]

;Load Kernel off Disk into RAM
lkernel:
	mov bx, KOFFSET
	mov dh, SECTORS_TO_LOAD
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]

;Start 32 Bit Real Mode
BEGIN_32_BIT:

;Execute Kernel, Hand over control to kernel.c
call KOFFSET
jmp $

;Pad the rest of bootsector with zeros
times 510 - ($-$$) db 0

;Magic number (boot signature) indicating this is a bootable sector
dw 0xaa55
