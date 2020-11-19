bits 16
org 0X7C00

mov eax,0x4567
call printHex

mov eax,0x4567
call printHex

mov eax,0x0
call printHex

mov eax,0x999
call printHex

jmp $
%include "./func/printHex.asm"
times 510 - ($ - $$) db 0
dw 0xAA55