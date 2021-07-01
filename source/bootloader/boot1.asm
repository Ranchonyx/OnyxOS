;Bootloader entry point at 0x7c00
org       0x7c00          ;BIOS loads this file at 0x7c00
bits      16              ;Currently 16-Bit real mode

;Jump to bootloader entry point
start: jmp loader_entry
; Define Hard(bass)coded strings
launch      db "[OnyxOS] Launching Bootloader..."     ,0
bootmsg_0   db "[OnyxOS] Bootloader Stage 1 Complete" ,0
bootmsg_1   db "[OnyxOS] Boot Stage 2 Complete"       ,0
bootmsg_2   db "[OnyxOS] Boot Stage 3 Complete"       ,0

;Include the retard standard assembly library
%include "../lib/rstdlib.asm"

;*************************************************;
;	Bootloader Entry Point
;*************************************************;
loader_entry:

mov si, launch
call Print

mov si, bootmsg_0
call Print

cli                       ;Clear all interrupts
hlt                       ;Halt the system


times 510 - ($-$$) db 0   ;Pad the rest of bootsector with zeros
dw 0xaa55                 ;Magic number (boot signature) indicating this is a bootable sector
