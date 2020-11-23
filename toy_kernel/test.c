#include "./kernel/util.h"
#include "./libc/mem.h"

#include <stdio.h>
#include <stdlib.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define OFF "\033[0m"

typedef struct _test_suite
{
    int (*test)();
    struct _test_suite *nxt;
} test_suite;

test_suite *head = 0;

void add_new_test(int (*test)())
{
    if (head == 0)
    {
        head = (test_suite *)malloc(sizeof(test_suite));
        head->nxt = 0;
        head->test = test;
        return;
    }
    else
    {
        test_suite *prevTemp = head, *nxtTemp = head->nxt;
        while (nxtTemp != 0)
        {
            prevTemp = prevTemp->nxt;
            nxtTemp = nxtTemp->nxt;
        }
        nxtTemp = (test_suite *)malloc(sizeof(test_suite));
        nxtTemp->nxt = 0;
        nxtTemp->test = test;
        prevTemp->nxt = nxtTemp;
    }
}

void clear(test_suite *now)
{
    if (now->nxt != 0)
        clear(now->nxt);
    free(now);
}

int run_test_cases()
{
    int cnt = 1;
    test_suite *_head = head;
    while (_head != 0)
    {
        if (head->test())
            printf("%sTest Case %d Passed%s\n", KGRN, cnt++, OFF);
        else
        {
            printf("%sTest Case %d Failed%s\n", KRED, cnt++, OFF);
            clear(head);
            return 1;
        }
        _head = _head->nxt;
    }
    clear(head);
    return 0;
}

int test1()
{
    int x, y;
    fromIdxToPos(666, &x, &y);
    int idx = fromPosToIdx(x, y);
    return (idx == 666);
}

int test2()
{
    int x = 12, y = 47;
    int xx, yy;
    int idx = fromPosToIdx(x, y);
    fromIdxToPos(idx, &xx, &yy);
    return (x == xx && y == yy);
}

int test3()
{
    char f = 0xFF;
    char f_ans = 0xF8;
    makeColor(&f, 0, 0, 0);
    char f2 = 0xFF;
    char f2_ans = 0x8F;
    makeBackgroundColor(&f2, 0, 0, 0);
    return (f == f_ans && f2 == f2_ans);
}

int test4()
{
    char src[] = "ABCDE";
    char dst[] = "00000";
    char src1[] = "NOT EQUAL";
    char src2[] = "not equal";
    mem_cpy(src, dst, 6);
    return (!mem_equ(src, dst) && mem_equ(src1, src2));
}

int test5()
{
    char len5str[] = "12345";
    return (str_len(len5str) == 5 && charToInt(len5str) == 12345);
}

int test6()
{
    unsigned char num = 0b10010011;
    unsigned char num2 = 0b00110101;
    unsigned char ans1 = 93;
    unsigned char ans2 = 35;
    return (bcdToInt(num) == ans1 && bcdToInt(num2) == ans2);
}
/* This code aims to test function used in kernel */
int main()
{
    add_new_test(test1);
    add_new_test(test2);
    add_new_test(test3);
    add_new_test(test4);
    add_new_test(test5);
    add_new_test(test6);
    return run_test_cases();
}