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
db 'ABCDE','Logo',0,'See the Logo for this toy OS',0

    pusha
    int 21

    mov ebx, LOGO
    mov ah,  0x0f
    mov ch,  0
    mov cl,  0
    int 20

    mov ebx, LOGO2
    mov ah, 0x0b
    mov ch, 1
    mov cl, 0
    int 20

    mov ebx, LOGO3
    mov ah, 0x0b
    mov ch, 15
    mov cl, 0
    int 20

    int 23
    popa
    ret

LOGO: db "Toy Kernel, Welcome you ",0
LOGO2: 
       db 10
       db "*** *** *** *** *** *** *** *** *** *** ***",10
       db "*** *** *** *** *** *** *** *** *** *** ***",10
       db 10
       db " ******  ******   **    **  ******  *******",10
       db "   **    *    *    **  **   *    *  *      ",10
       db "   **    *    *     ****    *    *  *******",10
       db "   **    *    *      **     *    *        *",10
       db "   **    ******      *      ******  *******",10
       db 10
       db "*** *** *** *** *** *** *** *** *** *** ***",10
       db "*** *** *** *** *** *** *** *** *** *** ***",10
       db 0

LOGO3:
db "__   __      __    __     ____           ",10
db "/\ \ /\ \    /\ \  /\ \   /\  _`\        "  ,10
db " \ `\`\/'/'   \ `\`\\/'/   \ \,\L\_\     ",10
db "  `\/ > <      `\ `\ /'     \/_\__ \     ",10
db "    \/'/\`\     `\ \ \       /\ \L\ \    ",10
db "    /\_\\ \_\     \ \_\      \ `\____\   ",10
db "    \/_/ \/_/      \/_/       \/_____/   ",0
                                   
                                   
                                                                          
times 0xA00 - ($ - $$) db 0

;sector4
addr equ 0x100000

db 'ABCDE','Calc Package Price',0,'Count the price you should pay for package',0
    pusha
    
    mov ebx,.MESSAGE
    mov ah,0x0f
    int 24
    xor eax, eax
    int 22 ; 获取数字输入
    ; EAX -> EDX:EAX
    mov ebx,.HELPSTR
    mov ah,0x0b
    int 24
    
    mov eax,[addr]
    mov bh,0x0f
    int 25
    cmp eax,5
    jg .above5
    mov eax,10
    jmp .finish

.above5:
    cmp eax,10
    jg .above10
    mov ebx,2
    mul ebx
    jmp .finish

.above10:
    mov ebx,3
    mul ebx
    sub eax,10

.finish:

    mov ebx,.OUTSTR
    push eax
    mov ah,0x0b
    int 24
    mov bh,0x0f
    pop eax
    int 25

    mov eax,10;
    ; int 26

    popa
    ret

.MESSAGE db "below 5kg, 10 yuan, 5kg to 10kg, 2 yuan per kg",10,"above 10kg, 3 yuan per kg => ",0
.HELPSTR db 10,"Your package weight => ",0
.OUTSTR db " Your total cost => ",0

times 0xC00 - ($ - $$) db 0

;sector5
db 'ABCDE','JumpHero',0,'To see a hero jumping upside down',0
    pusha

    ;ch -> x , cl -> y
    ;让这个小人跳来跳去，设置俩个变量，esp + 4 , esp + 8 表示 x，y的速度?
    mov ch,15
    mov cl,30
    mov dword [esp + 4],-1 ; x速度 向上 
    mov dword [esp + 8],1 ; y速度 向右
    mov edx,2500 ; 1000 frame to die


.loop:
    int 21
    mov ebx, .hero
    mov ah, 0x0c
    int 27
    mov eax,1000
    int 26
    ;Process Animation 
    add ch,[esp+4]
    add cl,[esp+8]
    cmp ch, 10 ; 10 就改向下
    jne .check10
    mov dword [esp+4], 1

.check10:
    cmp ch, 20 ; 20 就改向上
    jne .xCheckOK
    mov dword [esp+4], -1
.xCheckOK:

    cmp cl,60
    jne .check50
    mov dword [esp+8], -1 ; 反复横跳

.check50:
    cmp cl,20
    jne .yCheckOK
    mov dword [esp+8], 1 ; 反复横跳
.yCheckOK:
    ;
    dec edx
    or edx,edx
    jnz .loop

    popa
    ret


.hero:  db "*  *-*  *",10
        db " * |*| * ",10
        db "  **_**  ",10
        db "   *|*   ",10
        db "   *|*   ",10
        db "   |*|   ",10
        db "   ***   ",10
        db "  ** **  ",10
        db " *     * ",0


times 0xE00 - ($ - $$) db 0

;sector6
db 'ABCDE','DrawFunc4',0,'This Program does not implement',0
    pusha

    popa
    ret
times 0xE50 - ($ - $$) db 0

;sector7
db 'ABCDE','DrawFunc5',0,'This Program does not implement',0
    pusha

    popa
    ret
times 0xF00 - ($ - $$) db 0

;sector8
db 'ABCDE','DrawFunc6',0,'This Program does not implement',0
    pusha

    popa
    ret
times 0x1000 - ($ - $$) db 0

;sector9
db 'ABCDE','DrawFunc7',0,'This Program does not implement',0
    pusha

    popa
    ret
times 0x1200 - ($ - $$) db 0

