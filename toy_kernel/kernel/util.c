#include "../ports/ports.h"
#include "../libc/mem.h"
#include "type.h"
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

void printChar(int idx, char str, char background)
{
    ((char *)0xb8000)[idx * 2] = str;
    ((char *)0xb8000)[idx * 2 + 1] = background;
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
            setCursorIdx(offset + idx * 2);
            continue;
        }
        ((char *)0xb8000)[offset + idx * 2] = *str;
        ((char *)0xb8000)[offset + idx * 2 + 1] = background;
        setCursorIdx(offset + idx * 2);
        offset += 2;
        ++str;
#ifdef RELEASE
        nop(waitTime);
#endif
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


int add_value(int a, int b)
{
    return a + b;
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
    setCursorIdx(0);
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
#ifndef RELEASE
    return;
#endif
    int nop_value = 0;
    for (int i = 0; i < count; ++i)
        for (int j = 0; j < count; ++j)
            ++nop_value;
}

void scrollOneLine()
{
    mem_cpy((i8 *)VIDEO_MEMORY + 160, (i8 *)VIDEO_MEMORY, 24 * 80 * 2);
    for (int i = 0; i < 160; ++i)
        ((u8 *)0xb8000)[i + 48 * 80] = (u8)0;
}

void waitForKey()
{
    //未实现，仅仅等待一下
    nop(UNITNOP6);
}

// The following functions define a portable implementation of rand and srand.
// Copy From OS-Dev
static unsigned long int next = 1;

int rand(void) // RAND_MAX assumed to be 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}

int str_len(char *str)
{
    int len = 0;
    while (*str++ != '\0' && ++len)
        ;
    return len;
}

int charToInt(char *str)
{
    //"1234" -> 1234
    int off = str_len(str);
    int ret = 0;
    while (off--)
        ret = ret * 10 + (*str++ - '0');
    return ret;
}

unsigned char bcdToInt(unsigned char byte)
{
    unsigned char res = 0;
    res = (byte & 0x10) + (byte & 0x20) * 2 + (byte & 0x40) * 4 + (byte & 0x80) * 8;
    res = (res << 4) + (byte & 0x1) + (byte & 0x2) * 2 + (byte & 0x4) * 4 + (byte & 0x8) * 8;
    return res;
}

void bcdTo2Bytes(unsigned char byte, char *high_byte, char *low_byte)
{
    *high_byte = (byte & 0xF0) >> 4;
    *low_byte = byte & 0x0F;
}

void putChar(char data, i8 color)
{
    int cur = getCursorIdx() >> 1;
    if (cur >= 25 * 80)
    {
        cur = 24 * 80;
        scrollOneLine();
    }
    printChar(cur, data, color);
    cur++;
    setCursorIdx(cur * 2);
}
void int_to_hex_ascii(int n, char str[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        str[i++] = n % 16 + '0';
        if (str[i - 1] > '9')
            str[i - 1] += 'A' - '9' - 1;
    } while ((n /= 16) > 0);

    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';
    int k = 0;
    for (k = 0, i = i - 1; k < i; ++k, --i)
    {
        int tmp = str[k];
        str[k] = str[i];
        str[i] = tmp;
    }
}
void int_to_ascii(int n, char str[])
{
    int i, sign;
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';
    int k = 0;
    for (k = 0, i = i - 1; k < i; ++k, --i)
    {
        int tmp = str[k];
        str[k] = str[i];
        str[i] = tmp;
    }
}

void putChars(char *data, i8 color)
{
    int cur = getCursorIdx() >> 1;

    while (*data != '\0')
    {
        if (cur >= 25 * 80)
        {
            cur = 24 * 80;
            scrollOneLine();
        }
        if (*data == '\n')
        {
            int x, y;
            fromIdxToPos(cur, &x, &y);
            y = 0;
            x++;
            cur = fromPosToIdx(x, y);
        }
        else
        {
            printChar(cur, *data, color);
            ++cur;
        }
        setCursorIdx(cur * 2);
        ++data;
    }
}

void backOneChar()
{
    int idx = getCursorIdx();
    idx -= 2;
    setCursorIdx(idx);
    putChar(' ', 0x0);
    setCursorIdx(idx);
}