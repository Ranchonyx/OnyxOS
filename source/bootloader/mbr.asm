;Bootloader entry point at 0x7c00
global _start;

[bits 16]
[org  0x7c00]          ;BIOS loads this file at 0x7c00
KOFFSET equ 0x9000
SECTORS_TO_LOAD equ 32

_start:
jmp loader_entry
asciitest     db "[OnyxOS] Printing available ASCII Characters",0
done          db "[OnyxOS] Done"                               ,0
launch        db "[OnyxOS] Starting Bootloader"                ,0
protmode_msg  db "[OnyxOS] Moving to 32-Bit Protected Mode"    ,0
error	        db "Disk Error / Load Error / No CPUID"			     ,0
BOOT_DRIVE    db 0

;Include the retard standard assembly library
%include "source/lib/asm/rstdlib.asm"

loader_entry:

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

mov bp, 0x9000
mov sp, bp

call lkernel
call sw32

jmp $

%include "source/lib/asm/disk.asm"
%include "source/lib/asm/gdt.asm"
%include "source/lib/asm/sw32.asm"
%include "source/lib/asm/print32.asm"

[bits 16]
lkernel:
	mov bx, KOFFSET
	mov dh, SECTORS_TO_LOAD
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]
BEGIN_32_BIT:


call KOFFSET
jmp $

times 510 - ($-$$) db 0   ;Pad the rest of bootsector with zeros
dw 0aa55h                 ;Magic number (boot signature) indicating this is a bootable sector
