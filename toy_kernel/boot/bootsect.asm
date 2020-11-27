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
    ;load second sector, 2-stage boot load the second boot loader and then load kernel
    mov bx, SECOND_SECTOR
    mov dh, 8; 工作程序扇区号
    mov dl, [BOOT_DRIVE]
    mov cl, 0x02
    call disk_load

    ;load kernel
    mov bx, KERNEL_OFFSET
    mov dh, 50 ; 随便写一个大一点的数字，让后面的文件可以加载进来，我猜
    mov cl, 0x0A ; 设置一下读取的扇区 
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
    call clear_screen
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
SECOND_SECTOR equ 0x7C00 + 0x200
BOOT_DRIVE db 0
MSG_START db 'Boot Start', 0
MSG_LOAD_KERNEL db 'Loading Kernel', 0
MSG_PROTECT_MODE db 'Kernel Start, Have a good time', 0
MSG_KEY_EVENT db 'Press key to next stage', 0

times 510 - ($ - $$) db 0
dw 0xAA55

;sector2
another_print:
    pusha
    mov ebx, WELCOME_AGAIN
    call print_string_pm    
    popa
    ret
    
WELCOME_AGAIN: db 'Hey Guys I Come Back, Do you like old stuff like this?I print from ASM LANG'
times 0x400 - ($ - $$) db 0

;sector3
db 'ABCDE','DrawFunc',0,'DESCRIPTION',0
times 0x600 - ($ - $$) db 0

;sector4
db 'ABCDE','DrawFunc2',0,'DESCRIPTION2',0
times 0x800 - ($ - $$) db 0

;sector5
db 'ABCDE','DrawFunc3',0,'DESCRIPTION3',0
times 0xA00 - ($ - $$) db 0

;sector6
db 'ABCDE','DrawFunc4',0,'DESCRIPTION4',0
times 0xC00 - ($ - $$) db 0

;sector7
db 'ABCDE','DrawFunc5',0,'DESCRIPTION5',0
times 0xE00 - ($ - $$) db 0

;sector8
db 'ABCDE','DrawFunc6',0,'DESCRIPTION6',0
times 0x1000 - ($ - $$) db 0

;sector9
db 'ABCDE','DrawFunc7',0,'DESCRIPTION7',0
times 0x1200 - ($ - $$) db 0

