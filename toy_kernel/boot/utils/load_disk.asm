disk_load:
    pusha 
    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02

    mov ch, 0x00
    mov dh, 0x00
    int 0x13
    jc error
    pop dx
    cmp al, dh
    jne secotr_eror
    popa
    ret

error:
    mov bx, DISK_ERROR
    call printbx
    call printnl 
    jmp $

secotr_eror: 
    mov bx, SECTOR_ERROR
    call printbx 
    call printnl 
    jmp $

DISK_ERROR: db 'Disk Error', 0
SECTOR_ERROR: db 'Sector Error', 0