bits 16; 使用16位段模式
org 7C00H; 定义偏移

start:
    mov ah,0x2; 读扇区
    mov al,1;读取1个扇区
    mov ch,0;cylinder index
    mov dh,0;head index
    mov cl,2; sector index
    ; mov cl,66; this will trigger error, uncomment this to check if jc works
    mov dl,[disk]; disk index
    ;es 缓冲区地址段值
    mov bx,sector2; 缓冲区地址偏移
    int 0x13;
    jc .err
    jmp sector2;

.err:
    mov ah,0xE ; TTY方式显示文字
    mov si,errMessage
.innerloop:
    lodsb
    or al,al;
    jz .loop;
    int 0x10;
    jmp .innerloop; 
.loop:
    jmp $

errMessage: db "error reading disk",0DH,0AH,0
disk: db 0;
times 510 - ($-$$) db 0 ;Padding byte 0
dw 0xAA55 ; Maigc Number
;; end of sector 1

sector2:

    mov ah,0xE ; TTY方式显示文字
    mov si,message;

.innerloop: ; 输出代码
    lodsb
    or al,al;
    jz .exit
    int 0x10;
    jmp .innerloop; 

.exit:
message: db "a more complex hello world",0DH,0AH,0
times 1024 - ($ - $$) db 0
;; end of sector 2