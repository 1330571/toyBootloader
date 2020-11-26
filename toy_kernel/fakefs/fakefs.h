#ifndef _H_FAKEFS
#define _H_FAKEFS
#include "../kernel/type.h"

void load_file(u8 *src, u8 *dst, u32 len);
void execute_file_by_jmp(u32 addr);
void execute_file_by_call(u32 addr);

struct fs
{
    char program_name[4];
    
};

#endif