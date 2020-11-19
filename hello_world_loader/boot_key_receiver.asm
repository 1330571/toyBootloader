bits 16; 使用16位段模式
org 7C00H; 定义偏移
start:
    mov ah,0xE ; TTY方式显示文字
    mov si,message;

.innerloop:
    lodsb
    or al,al;
    jz .clear
    int 0x10;
    jmp .innerloop; 


.clear: ; 清空缓冲区
    mov ah,1 
    int 0x16; 判断缓冲区是否已经清空，ZF为清空完成的标志
    jz .ok ; 缓冲区已经清空
    mov ah, 0 
    int 0x16; 读出一个字符
    jmp .clear; 

.ok:
    mov ah,0; 设置读入命令
    int 0x16; 读入中断

    mov ah,0xE; 设置为TTY输出模式
    int 0x10; 输出刚刚读入的字符
        
    jmp .ok;

message db 'Press any key, then it will echo its ascii code',0DH,0AH,0 ; 字符串，换行，光标，截断
times 510 - ($-$$) db 0 ;Padding byte 0
dw 0xAA55 ; Maigc Number
