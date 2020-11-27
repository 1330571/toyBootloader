#include "fakefs.h"
#include "../kernel/type.h"
#include "../kernel/util.h"
#include "../libc/string.h"

void load_file(u8 *src, u8 *dst, u32 len)
{
    for (int i = 0; i < len; ++i)
        *dst++ = *src++;
}

void execute_file_by_jmp(u32 addr)
{
    __asm__ volatile(
        "jmp %%eax"
        :
        : "a"(addr)
        :);
}

void execute_file_by_call(u32 addr)
{
    __asm__ volatile(
        "call %%eax"
        :
        : "a"(addr)
        :);
}

fs file[16];
static int cnt = 0;

void build_up_mem_map()
{
    char *mem = STARTMEMORY;
    while (mem < ENDMEMORY)
    {
        if (!mem_equ_ctl_by_src2(mem, EXE_SIGNATURE)) //可执行文件标识
        {
            mem += 5;
            while (*mem != '\0')
                file[cnt].program_name[file[cnt].len++] = *mem++;
            file[cnt].program_name[file[cnt].len++] = '\0';

            ++mem; //跳过字符串截断


            //程序描述
            while (*mem != 0)
                append(file[cnt].description, *mem++);
            ++mem;
            file[cnt].start_addr = (int)mem;

            putChars("executable detected ", BLACK_WHITE);
            putChars((i8 *)file[cnt].program_name, BLACK_GREEN);
            putChars(" addr ", BLACK_WHITE);
            char buffer[32];
            putChars(" 0X", BLACK_BLUE);
            int_to_hex_ascii(file[cnt].start_addr, buffer);

            putChars(buffer, BLACK_BLUE);
            nop(UNITNOP10);

            putChars("\n", 0x0f);

            putChars(file[cnt].description, BLACK_RED);
            putChars("\n", 0x0f);
            ++cnt;
        }
        ++mem;
    }
}