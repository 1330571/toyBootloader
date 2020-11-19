; Custom Interrupt
bits 16
org 7C00H 

jmp start; 

div_handler:
    sti
    pusha
    mov bp,sp ; bp变为sp，通过加法寻址寻找返回地址
    
    mov bx,err_message
    call printstr
    ; 如果除法指令字节数超过2 
    ; 有关出错的说明，请查阅i386 manual
    add word[bp + 16], 2; 返回地址 + 2 以免无限执行div命令
    ; I think the stack frame look like this
    ; EFLAGS 
    ; CS bp + 18
    ; IP bp + 16
    ; 8 registers bp ~ bp + 14
    ; Local Variables
    popa
    iret
    
err_message db "Error Division Operation!",0XD,0XA,0;

%include "./func/print.asm"

start:
    ; mov cs,ds 
    mov ax,0;
    mov ds,ax ;中断向量
    cli
    mov word[0*4],div_handler ;偏移
    mov [0*4+2],cs ;段值
    sti


    mov eax,0xFFFF
    mov edx,0xFFFF
    mov ebx,0x1
    idiv ebx; 溢出
    
    mov bx,outside_message
    call printstr

outside_message db "After Division",0xD,0xA,0
times 510 - ($ - $$) db 0
dw 0xAA55