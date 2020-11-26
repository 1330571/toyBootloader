#include "fakefs.h"
#include "../kernel/type.h"

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