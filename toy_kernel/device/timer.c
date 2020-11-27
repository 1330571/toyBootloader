#include "timer.h"
#include "../kernel/type.h"
#include "../kernel/util.h"
#include "../ports/ports.h"
#include "../interrupts/isr.h"

u32 booting_tick = 0;
static void timer_callback(registers_t regs)
{
    ++booting_tick;
    if (booting_tick % 50 != 0)
        return;
#ifdef DETAIL
    putChars("Tick: ", 0x0f);
    char tick_data[256];
    int_to_ascii(booting_tick, tick_data);
    putChars(tick_data, 0x0f);
    putChars("\n", 0x0f);
#endif
}

void init_timer(unsigned int frequency)
{
    register_interrupt_handler(IRQ0, timer_callback);
    /*
     * Mode 2 – Rate Generator
     * Next falling edge of the (1.193182 MHz) input signal.
     */
    u32 div = 1193182 / frequency;
    u8 low = (u8)(div & 0xff);
    u8 high = (u8)((div & 0xff00) >> 8);
    byte_out(0x43, 0x36); //0011 1100
    byte_out(0x40, low);
    byte_out(0x40, high);
}
