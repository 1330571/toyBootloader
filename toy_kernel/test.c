#include "./kernel/util.h"
#include "./libc/mem.h"

#include <stdio.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define OFF "\033[0m"

void test1()
{
    int x, y;
    fromIdxToPos(666, &x, &y);
    int idx = fromPosToIdx(x, y);
    if (idx == 666)
        printf("%sTest Case 1 Passed\n", KGRN);
    else
        printf("%sTest Case 1 Error \n", KRED);
    printf("%s", OFF);
}

void test2()
{
    int x = 12, y = 47;
    int xx, yy;
    int idx = fromPosToIdx(x, y);
    fromIdxToPos(idx, &xx, &yy);
    if (x == xx && y == yy)
        printf("%sTest Case 2 Passed\n", KGRN);
    else
        printf("%sTest Case 2 Error \n", KRED);
    printf("%s", OFF);
}

void test3()
{
    char f = 0xFF;
    char f_ans = 0xF8;
    makeColor(&f, 0, 0, 0);
    char f2 = 0xFF;
    char f2_ans = 0x8F;
    makeBackgroundColor(&f2, 0, 0, 0);

    if (f == f_ans && f2 == f2_ans)
        printf("%sTest Case 3 Passed\n", KGRN);
    else
        printf("%sTest Case 3 Error \n", KRED);
    printf("%s", OFF);
}

void test4()
{
    char src[] = "ABCDE";
    char dst[] = "00000";
    char src1[] = "NOT EQUAL";
    char src2[] = "not equal";

    mem_cpy(src, dst, 6);
    if (!mem_equ(src, dst) && mem_equ(src1, src2))
        printf("%sTest Case 4 Passed\n", KGRN);
    else
        printf("%sTest Case 4 Error \n", KRED);
    printf("%s", OFF);
}

/* This code aims to test function used in kernel */
int main()
{
    test1();
    test2();
    test3();
    test4();

    return 0;
}