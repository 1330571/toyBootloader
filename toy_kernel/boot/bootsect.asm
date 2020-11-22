bits 16
org 0X7C00

    mov [BOOT_DRIVE], dl ; 初始化的dl值
    mov bp,0x9000
    mov sp,bp ; 设置栈的地址，安全地址

    mov bx, MSG_START
    call print_and_wait
    call load_kernel ; 加载后面的文件 
    call activate_procted_mode ; 启动保护模式
    jmp $

load_kernel : 
    mov bx, MSG_LOAD_KERNEL
    call print_and_wait
    mov bx,KERNEL_OFFSET
    mov dh, 16 ; 随便写一个大一点的数字，让后面的文件可以加载进来，我猜
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

print_and_wait:
    call printbx
    call printnl
    mov bx,MSG_KEY_EVENT
    call printbx
    call printnl
    call waitforkey
    ret

bits 32
into_kernel: 
    mov ebx, MSG_PROTECT_MODE
    call print_string_pm
    call KERNEL_OFFSET
    jmp $

%include "./boot/utils/key.asm"
%include "./boot/utils/print.asm"
%include "./boot/utils/load_disk.asm"

%include "./boot/activate_pm.asm"
%include "./boot/gdt_table.asm"

CONST_VARIABLESL: 

KERNEL_OFFSET equ 0x1000
BOOT_DRIVE db 0
MSG_START db 'Boot Start', 0
MSG_LOAD_KERNEL db 'Loading Kernel', 0
MSG_PROTECT_MODE db 'Press key to into kernel', 0
MSG_KEY_EVENT db 'Press key to next stage', 0

times 510 - ($ - $$) db 0
dw 0xAA55
