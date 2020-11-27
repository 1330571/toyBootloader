#ifndef _H_TIMER
#define _H_TIMER
#include "../kernel/type.h"
void init_timer(unsigned int frequency);
extern u32 booting_tick;
#endif