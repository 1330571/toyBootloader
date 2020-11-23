#include "../kernel/type.h"

void refresh_display();
void writeVga(u32 idx, u8 data, u8 attr);
void nextState();
void initState();