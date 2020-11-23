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

;清除屏幕
clear_screen:
    pusha

    mov edx, VIDEO_MEMORY
    mov cx,0xFA0
    xor ax,ax

.clear_loop: 
    mov [edx], ax
    add edx, 2
    loop .clear_loop
    
    popa       
    ret

; this only works for 16-bit real mode
; clear_screen:
;     pusha

;     mov ax,es
;     push ax

;     mov ax,0xb800
;     mov es,ax
    
;     xor bx,bx;
;     mov cx,0xFA0

; .clear_loop:
;     mov word [es:bx],0
;     add bx,2
;     loop .clear_loop

;     pop ax
;     mov es,ax

;     popa
;     ret