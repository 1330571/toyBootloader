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

