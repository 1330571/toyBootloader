; ax is the register for the number you want to print
printHex:
    pusha
    ;conver from binary to hex
    mov ebx, 0x10 ; base number
    xor ecx,ecx ; Count for the hex numbers
    cwd
    or eax,eax
    jz .back ; if eax = 0 , return from this function
.loop:
    or eax,eax
    jz .out

    div ebx
    call goAscii
    push edx
    xor edx,edx
    inc ecx
    jmp .loop

.out:
    ;start puts hex ASCII
    mov ah,0xE
    mov al,'0'
    int 0x10
    mov al,'X'
    int 0x10

.printLoop:
    pop edx
    mov al,dl
    int 0x10
    loop .printLoop

    mov al,0xD ;finish converting and puts new line
    int 0x10
    mov al,0xA
    int 0x10
.back:
    popa
    ret

goAscii:
    cmp dl,9
    ja .alpha
    add dl,'0'
    jmp .end    
.alpha:
    add dl,'A'
    sub dl,10
.end:
    ret

