bits 16; 使用16位段模式
org 7C00H; 定义偏移

start:
    ;start to move, move myself to 0000:0600H
    xor ax,ax
    mov ss,ax
    mov sp,7C00H ;栈顶设置为07C00
    mov es,ax ;target segment 
    mov dx,ax ;source segment
    mov si,0x7c00 ;source offset
    mov di,0x0600 ;target offset
    mov cx,0x0200 ;size
    cld ; clear the direction flag
    repz movsb
    push ax
    mov ax, 0x600 + .newStart - $$
    push 0x600 + .newStart - $$
    call printHex
    retf

.newStart:
    ;finish moving, then print the message after move myself to another memory addr
    mov ah,0xE ; TTY方式显示文字
    mov si,statusMessage
.innerloop:
    lodsb
    or al,al;
    jz .loop;
    int 0x10;
    jmp .innerloop; 

.loop:
    jmp $;

%include "./func/printHex.asm"
statusMessage: db "I move myself to another memory address",0DH,0AH,0
times 510 - ($ - $$) db 0
dw 0xAA55;