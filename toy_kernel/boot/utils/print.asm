bits 16
printbx:
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

bits 32
VIDEO_MEMORY equ 0xb8000
WHITE_BLACK  equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

.print_string_pm_loop:
    mov al, [ebx]
    mov ah, WHITE_BLACK

    or al,al
    je .done

    mov [edx], ax;
    inc ebx ; iterate to next char
    add edx, 2 ; 字节数据，属性，一次占用2个字节

    jmp .print_string_pm_loop
.done:
    popa
    ret