#include "util.h"
#include "type.h"
#include "../libc/mem.h"
#include "../device/timer.h"

void newStart()
{
    putChars("> ", BLACK_WHITE);
}

void terminal(char *str)
{
    if (!mem_equ(str, "hello"))
        putChars("Hello, work men, who are human above human\n", BLACK_BLUE);
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
}