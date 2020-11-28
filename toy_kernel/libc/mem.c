#include "string.h"

void mem_cpy(char *src, char *dst, unsigned int len)
{
    for (unsigned int i = 0; i < len; ++i)
        dst[i] = src[i];
}

char mem_equ(char *src, char *src2)
{
    while (1)
    {
        if (*src != *src2)
            return *src - *src2;
        if (*src == '\0')
            return 0;
        src++, src2++;
    }
}

char mem_equ_ignore_case(char *src, char *src2)
{
    while (1)
    {
        if (to_lower(*src) != to_lower(*src2))
            return *src - *src2;
        if (*src == '\0')
            return 0;
        src++, src2++;
    }
}
char mem_equ_ctl_by_src2(char *src, char *src2)
{
    if (src2 == '\0')
        return -1;
    while (1)
    {
        if (*src2 == 0)
            return 0;
        if (*src != *src2)
            return *src - *src2;
        src++, src2++;
    }
}