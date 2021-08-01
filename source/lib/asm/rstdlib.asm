;**************************************
; Prints a newline (0xdh, 0xah)
;**************************************
PrintNewline:
mov al, 0Dh
mov ah, 0eh
int 10h
mov al, 0Ah
int 10h
ret

;**************************************
;	Prints a string
;	DS=>SI: 0 terminated string
;**************************************
PrintString:
			xor 			ax,ax
			mov 			ds,ax
			mov 			es,ax
			lodsb
			or				al, al
			jz				PrintDone
			mov				ah,	0eh
			int				10h
			jmp				PrintString
PrintDone:
			cmp bl, 1
			je PrintNewline
			xor 	ax,ax
			int 	0x12
			ret

;**************************************
; Print all Ascii Characters
;**************************************
PrintAsciiCharacters:
loop:
inc al
cmp al, 255
je exit
mov ah, 0eh
int 10h
cmp bl, 1
jmp loop
exit:
ret

;**************************************
; Clear the screen
;**************************************
Clearscr:
pusha
mov ah, 0x00
mov al, 0x03  ; text mode 80x25 16 colours
int 0x10
popa
ret
