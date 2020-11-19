; bx is the string's address you want to print
printstr:
    pusha
.start:
    mov al,[bx]
    or al,al
    jz .done

    mov ah,0xE
    int 0x10

    inc bx
    jmp .start

.done:
    popa
    ret

printnl:
    pusha
    
    mov ah,0xE
    mov al,0x0A
    int 0x10
    mov al,0x0D
    int 0x10

    popa
    ret 
