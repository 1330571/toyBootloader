#ifndef _H_FAKEFS
#define _H_FAKEFS

#include "../kernel/type.h"
#include "../libc/mem.h"

void load_file(u8 *src, u8 *dst, u32 len);
void execute_file_by_jmp(u32 addr);
void execute_file_by_call(u32 addr);

#define STARTMEMORY (char *)0x8000
#define ENDMEMORY (char *)0x9000
#define EXE_SIGNATURE "ABCDE"

void build_up_mem_map();
typedef struct _fs
{
    u8 program_name[20];
    u8 description[32];
    u8 len;
    u32 start_addr;
} fs;

#endif