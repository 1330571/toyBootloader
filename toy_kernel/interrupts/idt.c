#include "idt.h"
#include "../kernel/util.h"

u16 low_16(u32 data)
{
    return data & 0x0000FFFF;
}

u16 high_16(u32 data)
{
    return (data & 0xFFFF0000) >> 16;
}
void set_idt_gate(int n, u32 handler)
{
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E; //1000 1110
    if (n == 32 || n == 33)
        idt[n].flags = 0xEE; // 更高的优先级
    idt[n].high_offset = high_16(handler);
}

void set_idt()
{
    idt_reg.base = (u32)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    __asm__ __volatile__("lidtl (%0)"
                         :
                         : "r"(&idt_reg));
}