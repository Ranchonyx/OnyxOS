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
; Prints a single character/value/register
; AL: register
;**************************************
PrintChar:
mov ah, 0eh
int 10h
cmp bl, 1
je PrintNewline
ret

;**************************************
;	Prints a string
;	DS=>SI: 0 terminated string
;**************************************
PrintString:
			xor 			ax,ax
			mov 			ds,ax
			mov 			es,ax
			lodsb					; load next byte from string from SI to AL
			or				al, al		; Is AL=0?
			jz				PrintDone	; Yep, null terminator found-bail out
			mov				ah,	0eh	; Nope Print the character
			int				10h
			jmp				PrintString		; Repeat until null terminator found
PrintDone:
			cmp bl, 1
			je PrintNewline
			xor 	ax,ax
			int 	0x12
			ret					; we are done, so return

;**************************************
; Print all Ascii Characters
;**************************************
PrintAsciiCharacters:
loop:
inc al
cmp al, 255
je exit
call PrintChar
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

;**************************************
; Print available memory
;**************************************
PrintMemory:
xor cx, cx
xor dx, dx
mov ax, 0xe801
int 0x15

;????? osdev is weird sometimes

mov ax, cx
mov bx, dx

shr al, 8
and ah, 0x00ff

call PrintChar
mov al, ah
call PrintChar
ret
