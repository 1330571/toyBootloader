; ax is the register for the number you want to print
printOct:
    pusha
    ;conver from binary to hex
    mov ebx, 10 ; base number
    xor ecx,ecx ; Count for the hex numbers
    cwd
    or eax,eax
    jz .back ; if eax = 0 , return from this function
.loop:
    or eax,eax
    jz .out

    div ebx
    call goAsciiOct
    push edx
    xor edx,edx
    inc ecx
    jmp .loop

.out:
    ;start puts hex ASCII
    mov ah,0xE

.printLoop:
    pop edx
    mov al,dl
    int 0x10
    loop .printLoop

.back:
    popa
    ret

goAsciiOct:
    add dl,'0'
    ret

