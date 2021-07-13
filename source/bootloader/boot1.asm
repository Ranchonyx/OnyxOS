;Bootloader entry point at 0x7c00
org       0x7c00          ;BIOS loads this file at 0x7c00
bits      16              ;Currently 16-Bit real mode

;Jump to bootloader entry point
start: jmp loader_entry
; Define Hard(bass)coded strings
asciitest     db "[OnyxOs] Printing available ASCII Characters",0
error         db "[OnyxOS] Error during Boot"                  ,0
done          db "[OnyxOS] Done"                               ,0
launch      	db "[OnyxOS] Starting Bootloader"                ,0
bootmsg_0   	db "[OnyxOS] Bootloader Stage 1 Complete"        ,0
bootmsg_1   	db "[OnyxOS] Bootloader Stage 2 Complete"        ,0
bootmsg_2     db "[OnyxOS] Bootloader Stage 3 Complete"        ,0

;Include the retard standard assembly library
%include "../lib/rstdlib.asm"


;*************************************************;
;	OEM Parameter block / BIOS Parameter Block
;*************************************************;

;TIMES 0Bh-$+start DB 0

bpbBytesPerSector:  	DW 512
bpbSectorsPerCluster: 	DB 1
bpbReservedSectors: 	DW 1
bpbNumberOfFATs: 	DB 2
bpbRootEntries: 	DW 224
bpbTotalSectors: 	DW 2880
bpbMedia: 	        DB 0xF0
bpbSectorsPerFAT: 	DW 9
bpbSectorsPerTrack: 	DW 18
bpbHeadsPerCylinder: 	DW 2
bpbHiddenSectors:       DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber: 	        DB 0
bsUnused: 	        DB 0
bsExtBootSignature: 	DB 0x29
bsSerialNumber:	        DD 0xa0a1a2a3
bsVolumeLabel: 	        DB "MOS FLOPPY "
bsFileSystem: 	        DB "FAT12   "

;*************************************************;
;	Bootloader Entry Point
;*************************************************;
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

mov si, bootmsg_0
call PrintString

call PrintMemory

cli                       ;Clear all interrupts
hlt                       ;Halt the system


times 510 - ($-$$) db 0   ;Pad the rest of bootsector with zeros
dw 0xaa55                 ;Magic number (boot signature) indicating this is a bootable sector
