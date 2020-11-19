bits 16; 使用16位段模式
org 7C00H; 定义偏移

start:
    mov ah,0xE ; TTY方式显示文字
    mov cx, 5  ; 输出5次Hello World

.printloop:
    mov si,message;
.innerloop:
    lodsb
    or al,al;
    jz .outprint
    int 0x10;
    jmp .innerloop; 
.outprint:
    loop .printloop
.finish:
    jmp $ ; 无限循环

message db 'Hello World',0DH,0AH,0 ; 字符串，换行，光标，截断
times 510 - ($-$$) db 0 ;Padding byte 0
dw 0xAA55 ; Maigc Number
