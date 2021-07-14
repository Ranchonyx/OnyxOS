gdt:

gdt_null:
  dq 0

gdt_code:
  dw 0FFFFH
  dw 0
  db 0
  db 10011010b
  db 11001111b
  db 0

gdt_data:
  dw 0FFFFH
  dw 0
  db 0
  db 10010010b
  db 11001111b
  db 0
gdt_end:

gdt_desc:
  dw gdt_end - gdt + 1
  dd gdt
