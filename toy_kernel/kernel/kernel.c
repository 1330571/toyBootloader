#include "util.h"
#include "../ports/ports.h"
#include "../life/life.h"
#include "../interrupts/isr.h"
char *video_memory = (char *)0xb8000;

char *hello_str = "Toy kernel, Thanks for trying this useless toy";
char *str1 = "This toy is working in progress and just write for homework";
char *str2 = "You can view source code to this project's github repository";
char *str3 = "repository URL:  https://github.com/1330571/toyBootloader/";
char *str4 = "Would you like to see the life game?\n\
A Celluar Automata defined in wiki\n\
And the very beginning of A Game Programmers' life\n\
Have a good time to see Cellulars' life";

char *finish_str = "That is a really cool thing, right?";
char *irq_install1 = "Arrange Interrupts    ......\nSetting IDT    ......\nA whole new kernel world will start    ......\n";
char *irq_install2 = "Interrupts were triggered by int instructions see it?\n";

char *work_program0 = "Select the program you want to load in\n";
char *work_program1 = "X. Press 1 to run -> ";
char *work_program2 = "X. Press 2 to run -> ";
char *work_program3 = "X. Press 3 to run -> ";
char *work_program4 = "X. Press 4 to run -> ";
char *work_program5 = "X. Press 5 to run -> ";
char *work_program6 = "X. Press 6 to run -> ";

char *program_name1 = "Program 1\n";
char *program_name2 = "Program 2\n";
char *program_name3 = "Program 3\n";
char *program_name4 = "Program 4\n";
char *program_name5 = "Program 5\n";
char *program_name6 = "Program 6\n";

void welcome_boot()
{
    int offset = fromPosToIdx(2, 0);
    printWithCursor(offset, hello_str, (char)0x0f, 0);
    offset = fromPosToIdx(3, 0);
    printWithCursor(offset, str1, (char)0x0f, 0);
    offset = fromPosToIdx(4, 0);
    printWithCursor(offset, str2, (char)0x0f, 0);
    char color = 0x0F;
    makeColor(&color, 0, 0, 1);
    offset = fromPosToIdx(5, 0);
    // printWithCursor(offset, str3, color, UNITNOP3);
    printWithCursor(offset, str3, color, 0);

    nop(UNITNOP5);
    clearScreen();
    nop(UNITNOP3);

    offset = fromPosToIdx(1, 0);
    makeColor(&color, 0, 1, 0);
    printWithCursor(offset, str4, color, UNITNOP2);
    nop(UNITNOP7);

    __asm__ volatile("call 0X7E00");

    nop(UNITNOP8);
    char txt_to_show[] = "Wait 5...";
    for (int i = 0; i < 5; ++i)
    {
        txt_to_show[5] = (5 - i) + '0';
        print(fromPosToIdx(24, 0), txt_to_show, 0x04);
        nop(UNITNOP7);
        scrollOneLine();
    }

    refresh_display();
    initState();
    int _cnt = 0;
#ifdef RELEASE
    while (_cnt++ < 100)
#else
    while (_cnt++ < 10)
#endif
    {
        nop(UNITNOP5);
        nextState();
        refresh_display();
    }
}
#define headpos 10
void main()
{
    // putChars("Bad\nDays",0x0f);

    setCursorIdx(0);
    //below code snippets is for printing single char,
    // for (int i = 0; i < 99999; ++i)
    // {
    //     putChar('A', 0x0f);
    //     nop(UNITNOP7);
    // }
    welcome_boot();
    clearScreen();
    printWithCursor(fromPosToIdx(0, 0), finish_str, 0x0b, UNITNOP4);
    printWithCursor(fromPosToIdx(1, 0), irq_install1, 0x0b, UNITNOP4);
    nop(UNITNOP8);
    isr_install();
    __asm__ volatile("int $2");
    __asm__ volatile("int $3");
    printWithCursor(getCursorIdx() >> 1, irq_install2, 0x0b, UNITNOP4);
    nop(UNITNOP8);
    clearScreen();
    setCursorIdx(0);
    printWithCursor(fromPosToIdx(headpos, 0), work_program0, 0x0b, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 1, 0), work_program1, 0x0b, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 2, 0), work_program2, 0x0b, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 3, 0), work_program3, 0x0b, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 4, 0), work_program4, 0x0b, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 5, 0), work_program5, 0x0b, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 6, 0), work_program6, 0x0b, UNITNOP2);

    printWithCursor(fromPosToIdx(headpos + 1, 21), program_name1, 0x0f, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 2, 21), program_name2, 0x0f, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 3, 21), program_name3, 0x0f, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 4, 21), program_name4, 0x0f, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 5, 21), program_name5, 0x0f, UNITNOP2);
    printWithCursor(fromPosToIdx(headpos + 6, 21), program_name6, 0x0f, UNITNOP2);
}
