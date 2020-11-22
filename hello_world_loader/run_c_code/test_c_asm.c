#include <stdio.h>
#include <stdlib.h>

int main()
{
    int src = 1;
    int dst = 12345;
    printf("src = %d dst = %d\n", src, dst);

    __asm__(
        "mov %1, %0\n\t"
        "add %1, %0"
        : "=r"(dst)
        : "r"(src));

    printf("src = %d dst = %d\n", src, dst);

    //% 变量 %% 寄存器
    __asm__(
        "mov %1, %%eax \n\t"
        "inc %%eax \n\t"
        "mov %%eax, %0"
        : "=r"(dst) // Output
        : "r"(src)  // Input
        : "%eax"    // Register
    );

    printf("src = %d dst = %d\n", src, dst);

    __asm__(
        "movl $0x6666, %0" // you should put $ and size prefix , l for 32 bits, w for 16 bits, b for 8 bits
        : "=r"(dst)
        :
        :);
    printf("src = %d dst = %d\n", src, dst);

    __asm__(
        "mov %%ecx,%0"
        : "=r"(src)
        : "c"(dst) //c means load dst to ecx, so mov ecx,%0 directly let src = dst
        :);
    printf("src = %d dst = %d\n", src, dst);

    src = 1;
    __asm__(
        "lea (%0,%0,4), %0"
        : "=r"(src)
        : "r"(src)
        :);
    printf("src = %d dst = %d\n", src, dst);

    return 0;
}