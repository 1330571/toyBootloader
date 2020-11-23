#include "util.h"
#include "../ports/ports.h"
#include "../life/life.h"

char *video_memory = (char *)0xb8000;

char *hello_str = "Toy kernel, Thanks for trying this useless toy";
char *str1 = "This toy is working in progress and just write for homework";
char *str2 = "You can view source code to this project's github repository";
char *str3 = "repository URL:  https://github.com/1330571/toyBootloader/";
char *str4 = "Would you like to see the life game?\n\
A Celluar Automata defined in wiki\n\
And the very beginning of A Game Programmers' life\n\
Have a good time to see Cellulars' life";

void main()
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
    printWithCursor(offset, str3, color, UNITNOP3);

    nop(UNITNOP5);
    clearScreen();
    nop(UNITNOP3);

    offset = fromPosToIdx(1, 0);
    makeColor(&color, 0, 1, 0);
    printWithCursor(offset, str4, color, UNITNOP2);
    
    nop(UNITNOP6);
    refresh_display();
    initState();
    while (1)
    {
        nop(UNITNOP5);
        nextState();
        refresh_display();
    }
}