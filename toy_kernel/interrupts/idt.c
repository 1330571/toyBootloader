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
/*
typedef struct
{
    u16 low_offset; 
    u16 sel;       
    u8 always0;
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" 
    u8 flags;
    u16 high_offset; 
} __attribute__((packed)) idt_gate_t;
*/
void set_idt_gate(int n, u32 handler)
{
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0xEE; //1000 1110
    if (n == 32 || n == 33)
        idt[n].flags = 0x8E; //1110 1110更高的优先级
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