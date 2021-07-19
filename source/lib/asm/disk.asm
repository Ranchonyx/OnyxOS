disk_load:
	pusha
	push dx

	mov ah, 0x02
	mov al, dh
	mov cl, 0x02

	mov ch, 0x00
	mov dh, 0x00

	int 0x13
	jc disk_err

	pop dx
	cmp al, dh

	jne sect_err
	popa
	ret

disk_err:
	mov si, error
	mov bl, 1
	call PrintString
	jmp disk_loop

sect_err:
	mov si, error
	mov bl, 1
	call PrintString
	jmp disk_loop

disk_loop:
	jmp $
