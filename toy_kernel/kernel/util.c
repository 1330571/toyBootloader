#include "../ports/ports.h"
#include "util.h"
#define REG_SCREEN_CTRL 0x3d4 //this is used for getting cursor position
#define REG_SCREEN_DATA 0x3d5
// 80 * 25
/*
@x x代表行数 
@y y代表列数
*/
int fromPosToIdx(int x, int y)
{
    return x * 80 + y;
}

void fromIdxToPos(int idx, int *x, int *y)
{
    *y = idx % 80;
    *x = idx / 80;
}

void print(int idx, char *str, char background)
{
    int offset = 0;
    while (*str != '\0')
    {
        ((char *)0xb8000)[offset + idx * 2] = *str;
        ((char *)0xb8000)[offset + idx * 2 + 1] = background;
        offset += 2;
        ++str;
    }
}

void printWithCursor(int idx, char *str, char background, int waitTime)
{
    if (waitTime == 0)
        waitTime = UNITNOP2;
    int offset = 0;
    while (*str != '\0')
    {
        if (*str == '\n')
        {
            ++str;
            int tmp_x, tmp_y;
            fromIdxToPos((offset >> 1) + idx, &tmp_x, &tmp_y);
            tmp_x++;
            tmp_y = 0;
            idx = fromPosToIdx(tmp_x, tmp_y);
            offset = 0;
            continue;
        }
        ((char *)0xb8000)[offset + idx * 2] = *str;
        ((char *)0xb8000)[offset + idx * 2 + 1] = background;
        setCursorIdx(offset + idx * 2);
        offset += 2;
        ++str;
        nop(waitTime);
    }
}

void makeColor(char *src, int r, int g, int b)
{
    //1111 1000 = F8
    *src = *src & 0xF8;
    *src = *src | (b != 0);
    *src = *src | ((g != 0) << 1);
    *src = *src | ((r != 0) << 2);
}

void makeBackgroundColor(char *src, int r, int g, int b)
{
    //1000 1111 = 8F
    *src = *src & 0x8F;
    *src = *src | ((b != 0) << 4);
    *src = *src | ((g != 0) << 5);
    *src = *src | ((r != 0) << 6);
}

void clearScreen()
{
    for (int i = 0; i < 4000; ++i)
        ((char *)0xb8000)[i] = 0;
}

int getCursorIdx()
{ //Copied from OS-tutorial 16
    byte_out(REG_SCREEN_CTRL, 14);
    int offset = byte_in(REG_SCREEN_DATA);
    byte_out(REG_SCREEN_CTRL, 15);
    offset <<= 8;
    offset += byte_in(REG_SCREEN_DATA);
    return offset << 1;
}

void setCursorIdx(int idx)
{ //Copied from OS-tutorial 16
    idx >>= 1;
    byte_out(REG_SCREEN_CTRL, 14);
    byte_out(REG_SCREEN_DATA, (unsigned char)(idx >> 8));
    byte_out(REG_SCREEN_CTRL, 15);
    byte_out(REG_SCREEN_DATA, (unsigned char)(idx & 0xff));
}

void nop(int count)
{
    int nop_value = 0;
    for (int i = 0; i < count; ++i)
        for (int j = 0; j < count; ++j)
            ++nop_value;
}