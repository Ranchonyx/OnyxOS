;***************************************
;	Prints a string
;	DS=>SI: 0 terminated string
;***************************************
Print:
			xor ax,ax
			mov ds,ax
			mov es,ax
			lodsb					; load next byte from string from SI to AL
			or			al, al		; Does AL=0?
			jz			PrintDone	; Yep, null terminator found-bail out
			mov			ah,	0eh	; Nope-Print the character
			int			10h
			jmp			Print		; Repeat until null terminator found
PrintDone:
			xor ax,ax
			int 0x12
			ret					; we are done, so return
