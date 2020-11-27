bits 16
org 0x7E00
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