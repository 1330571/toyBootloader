#include "isr.h"
#include "../kernel/util.h"
#include "../ports/ports.h"
#include "../device/keyboard.h"
#include "../device/timer.h"

#include "idt.h"

isr_t interrupt_handlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */

void isr_install()
{
    set_idt_gate(0, (u32)isr0);
    set_idt_gate(1, (u32)isr1);
    set_idt_gate(2, (u32)isr2);
    set_idt_gate(3, (u32)isr3);
    set_idt_gate(4, (u32)isr4);
    set_idt_gate(5, (u32)isr5);
    set_idt_gate(6, (u32)isr6);
    set_idt_gate(7, (u32)isr7);
    set_idt_gate(8, (u32)isr8);
    set_idt_gate(9, (u32)isr9);
    set_idt_gate(10, (u32)isr10);
    set_idt_gate(11, (u32)isr11);
    set_idt_gate(12, (u32)isr12);
    set_idt_gate(13, (u32)isr13);
    set_idt_gate(14, (u32)isr14);
    set_idt_gate(15, (u32)isr15);
    set_idt_gate(16, (u32)isr16);
    set_idt_gate(17, (u32)isr17);
    set_idt_gate(18, (u32)isr18);
    set_idt_gate(19, (u32)isr19);
    set_idt_gate(20, (u32)isr20);
    set_idt_gate(21, (u32)isr21);
    set_idt_gate(22, (u32)isr22);
    set_idt_gate(23, (u32)isr23);
    set_idt_gate(24, (u32)isr24);
    set_idt_gate(25, (u32)isr25);
    set_idt_gate(26, (u32)isr26);
    set_idt_gate(27, (u32)isr27);
    set_idt_gate(28, (u32)isr28);
    set_idt_gate(29, (u32)isr29);
    set_idt_gate(30, (u32)isr30);
    set_idt_gate(31, (u32)isr31);

    // Remap the PIC
    byte_out(0x20, 0x11);
    byte_out(0xA0, 0x11);
    byte_out(0x21, 0x20);
    byte_out(0xA1, 0x28);
    byte_out(0x21, 0x04);
    byte_out(0xA1, 0x02);
    byte_out(0x21, 0x01);
    byte_out(0xA1, 0x01);
    byte_out(0x21, 0x0);
    byte_out(0xA1, 0x0);

    // Install the IRQs
    set_idt_gate(32, (u32)irq0); //0 - Programmable interrupt Timer interrupt
    set_idt_gate(33, (u32)irq1);
    set_idt_gate(34, (u32)irq2);
    set_idt_gate(35, (u32)irq3);
    set_idt_gate(36, (u32)irq4);
    set_idt_gate(37, (u32)irq5);
    set_idt_gate(38, (u32)irq6);
    set_idt_gate(39, (u32)irq7);
    set_idt_gate(40, (u32)irq8);
    set_idt_gate(41, (u32)irq9);
    set_idt_gate(42, (u32)irq10);
    set_idt_gate(43, (u32)irq11);
    set_idt_gate(44, (u32)irq12);
    set_idt_gate(45, (u32)irq13);
    set_idt_gate(46, (u32)irq14);
    set_idt_gate(47, (u32)irq15);

    set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

void handle_print(registers_t *r)
{
    char *buffer = (u8 *)r->ebx;
    char color = (r->eax >> 8) & 0xff;
    char x = (r->ecx >> 8) & 0xff;
    char y = r->ecx & 0xff;
    printWithCursor(fromPosToIdx(x, y), buffer, color, UNITNOP2);
}
void handle_print2(registers_t *r)
{
    char *buffer = (u8 *)r->ebx;
    char color = (r->eax >> 8) & 0xff;
    putChars(buffer, color);
}
void handle_output(registers_t *r)
{
    char buffer[10];
    char color = (r->ebx >> 8) & 0xff;
    int_to_ascii(r->eax, buffer);
    putChars(buffer, color);
}

#define valueAddr (u32 *)0x100000
void isr_handler(registers_t r)
{
    switch (r.int_no)
    {
    case 20:
    {
        handle_print(&r);
        break;
    }
    case 21:
    {
        clearScreen();
        break;
    }
    case 22:
    {
        reset();
        keyState = 666; //wait for Int Input

        while (keyState == 666)
            keyboard_callback(r);

        char buffer[32];
        int_to_ascii(value, buffer);

        *valueAddr = value;

#ifdef DETAIL
        putChars("Your Input => ", BLACK_RED);
        putChars(buffer, 0x0f);
#endif
        break;
    }
    case 23:
    {
        char b[] = "\nPress key to continue";
        putChars(b, 0x0f);
        nop(UNITNOP7);
        u8 scancode = byte_in(0x60);
        while (1)
        {
            u8 scancode2 = byte_in(0x60);
            if (scancode2 > 57)
                scancode2 = scancode;
            if (scancode2 != scancode)
                break;
        }

        break;
    }
    case 24:
    {
        handle_print2(&r);
        break;
    }
    case 25:
    {
        handle_output(&r);
        break;
    }
    case 26:
    {
    }
    default:
    {
        putChars("Interrupt is triggered\n", 0x0b);
        char s[32];
        int_to_ascii(r.int_no, s);
        putChars(s, 0x0f);
        putChars("    ", 0x0f);
        putChars(exception_messages[r.int_no], 0x0f);
        putChars("   eax=", 0x0f);
        char buffer[32];
        int_to_ascii(r.eax, buffer);
        putChars(buffer, 0x0f);
        putChars("\n", 0x0f);
    }
    }
}

void register_interrupt_handler(u8 n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r)
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40)
        byte_out(0xA0, 0x20); /* slave */
    byte_out(0x20, 0x20);     /* master */

    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}