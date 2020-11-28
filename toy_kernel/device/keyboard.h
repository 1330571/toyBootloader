#include "../interrupts/idt.h"
#include "../interrupts/isr.h"
extern int keyState;
extern int value;

void init_keyboard();
void keyboard_callback(registers_t regs);
void reset();