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
%include "rstdlib.asm"

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

%include "disk.asm"
%include "gdt.asm"
%include "sw32.asm"
%include "print32.asm"

[bits 16]
lkernel:
	mov bx, KOFFSET
	mov dh, SECTORS_TO_LOAD
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]
BEGIN_32_BIT:
; ;Check if CPUID is supported
; pushfd                               ;Save EFLAGS
; pushfd                               ;Store EFLAGS
; xor dword [esp],0x00200000           ;Invert the ID bit in stored EFLAGS
; popfd                                ;Load stored EFLAGS (with ID bit inverted)
; pushfd                               ;Store EFLAGS again (ID bit may or may not be inverted)
; pop eax                              ;eax = modified EFLAGS (ID bit may or may not be inverted)
; xor eax,[esp]                        ;eax = whichever bits were changed
; popfd                                ;Restore original EFLAGS
; and eax,0x00200000                   ;eax = zero if ID bit can't be changed, else non-zero
;
; cmp eax, 0
; jne kstart
; mov eax, 00h
; cpuid
; call print32

call KOFFSET
jmp $

times 510 - ($-$$) db 0   ;Pad the rest of bootsector with zeros
dw 0aa55h                 ;Magic number (boot signature) indicating this is a bootable sector
