#include "util.h"
#include "type.h"
#include "../libc/mem.h"
#include "../device/timer.h"
#include "../fakefs/fakefs.h"
#include "../fakefs/fakefs.h"

void newStart()
{
    putChars("> ", BLACK_WHITE);
}
void help_exec(char *str)
{
    int flag = 0;
    for (int i = 0;; i++)
    {
        if (file[i].len == 0)
            break;
        if (!mem_equ_ignore_case(str, file[i].program_name))
        {
            flag = 1;
            putChars(file[i].program_name, BLACK_WHITE);
            putChars("    ", 0x0f);
            putChars(file[i].description, BLACK_GREEN);
            putChars("\n", 0x0f);
            break;
        }
    }
    if (!flag)
    {
        putChars("No this executeable file", BLACK_RED);
        putChars("\n", BLACK_WHITE);
    }
}

void run_exec(char *str)
{
    int flag = 0;
    for (int i = 0;; i++)
    {
        if (file[i].len == 0)
            break;
        if (!mem_equ_ignore_case(str, file[i].program_name))
        {
            putChars("Running... ", 0x0f);
            putChars(file[i].program_name, 0x0f);
            putChars("\n", 0x0f);
            flag = 1;
            // load_file(file[i].start_addr, 0x10000, 0x200);
            nop(UNITNOP10);
            execute_file_by_call(file[i].start_addr);
            putChars("\n", 0x0f);
            // execute_file_by_call((unsigned int)0x10000);
            break;
        }
    }
    if (!flag)
    {
        putChars("No this executeable file", BLACK_RED);
        putChars("\n", BLACK_WHITE);
    }
}

void list()
{
    for (int i = 0;; i++)
    {
        if (file[i].len == 0)
            break;
        char buffer[32];
        int_to_ascii(i + 1, buffer);
        putChars(buffer, BLACK_WHITE);
        putChars("    ", 0x0f);
        putChars(file[i].program_name, BLACK_GREEN);
        putChars("\n", BLACK_WHITE);
    }
}
void terminal(char *str)
{
    if (!mem_equ(str, "hello"))
        putChars("Hello, code men, who are human above human\n", BLACK_BLUE);
    if (!mem_equ(str, "clear"))
        clearScreen();
    if (!mem_equ(str, "whoami"))
        putChars("You are admin and the only admin user of this toy OS\n", BLACK_WHITE);
    if (!mem_equ(str, "time"))
    {
        putChars("Time(toy unit) since booted => ", BLACK_WHITE);
        char txt[32];
        int_to_ascii(booting_tick, txt);
        putChars(txt, BLACK_WHITE);
        putChars("\n", BLACK_WHITE);
    }
    if (!mem_equ(str, "quit"))
    {
        putChars("See You Next Time", BLACK_GREEN);
        while (1)
            ;
    }
    if (!mem_equ(str, "ls"))
    {
        list();
    }
    if (!mem_equ_ctl_by_src2(str, "help"))
    {
        str += 5;
        help_exec(str);
    }
    if (!mem_equ_ctl_by_src2(str, "run"))
    {
        str += 4;
        run_exec(str);
    }
}