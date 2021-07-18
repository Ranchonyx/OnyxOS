;Bootloader entry point at 0x7c00
bits 16
org  0x7c00          ;BIOS loads this file at 0x7c00

start: jmp loader_entry
; Define Hard(bass)coded strings
asciitest     db "[OnyxOs] Printing available ASCII Characters",0
done          db "[OnyxOS] Done"                               ,0
launch      	db "[OnyxOS] Starting Bootloader"                ,0
bootmsg_0   	db "[OnyxOS] Bootloader Stage 1 Complete"        ,0
protmode_msg  DB "[OnyxOS] Moving to 32-Bit Protected Mode"    ,0


;Include the retard standard assembly library
%include "./rstdlib.asm"

loader_entry:

call Clearscr

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

cli

xor ax, ax
mov ds, ax

lgdt [gdt_desc]

mov eax, cr0
or eax, 1
mov cr0, eax

; Longjump to 32-Bit area
; YAAAYYY
jmp 08h:clear_pipe

bits 32
%include "./rstdlib32.asm"
clear_pipe:
; Magic happens after this line
; Do not use rstdlib anymore
; Refer to rstdlib32
mov ax, 10h
mov ds, ax
mov ss, ax

mov esp, 090000h

mov byte [ds:0B8000h], 'P'      ; Move the ASCII-code of 'P' into first video memory
mov byte [ds:0B8001h], 1Ch      ; Assign a color code

call hang

%include "./gdt.asm"


times 510 - ($-$$) db 0   ;Pad the rest of bootsector with zeros
dw 0aa55h                 ;Magic number (boot signature) indicating this is a bootable sector
