unsigned char byte_in(unsigned short portNumber)
{
    unsigned char res;
    __asm__ volatile(
        "in %%dx,%%al"
        : "=a"(res)
        : "d"(portNumber)
        :);
    return res;
}

void byte_out(unsigned short portNumber, unsigned char data)
{
    __asm__ volatile(
        "out %%al,%%dx"
        :
        : "d"(portNumber), "a"(data)
        :);
}