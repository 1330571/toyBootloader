bits 16
org 0X7C00

    push cs
    pop ds
    ;70H端口是索引端口，71H端口是数据端口，就可以通过这种方式来获取大量的寄存器值
.LoopClock:
    mov al, 2
    out 70H, al 
    in al,71H
    mov [minute], al

    mov al, 0 
    out 70H, al 
    in al, 71H 
    mov [second], al

    mov al,[minute]
    call EchoValue
    mov al,':'
    call PutChar

    mov al, [second]
    call EchoValue

    mov al, 0DH ; start a new line 
    call PutChar
    mov al, 0AH 
    call PutChar

    jmp .LoopClock

; There is some error if we directly print the minute and second value
EchoValue: 
    push ax
    shr al, 4
    add al,'0' 
    call PutChar 
    pop ax 
    and al,0x0F
    add al,'0' 
    call PutChar 
    ret

PutChar:   
    mov bh, 0
    mov ah,14 
    int 0x10
    ret

    second: db 0
    minute: db 0
    times 510 - ($ - $$) db 0
    dw 0XAA55