//80 * 25
#include "../libc/mem.h"
#include "../kernel/util.h"
#include "../kernel/type.h"
#include "../ports/ports.h"

u16 vga[VIDEO_SIZE];
u8 cell[VIDEO_SIZE];

void renderDisplay();
void nextState();
void initState();

void writeVga(u32 idx, u8 data, u8 attr)
{
    vga[idx] = attr << 8 | data;
}

/*
rule copied from : https://www.zhihu.com/topic/19649581/hot
每个细胞有两种状态 - 存活或死亡，每个细胞与以自身为中心的周围八格细胞产生互动（如图，黑色为存活，白色为死亡）
当前细胞为存活状态时，当周围的存活细胞低于2个时（不包含2个），该细胞变成死亡状态。（模拟生命数量稀少）
当前细胞为存活状态时，当周围有2个或3个存活细胞时，该细胞保持原样。
当前细胞为存活状态时，当周围有超过3个存活细胞时，该细胞变成死亡状态。（模拟生命数量过多）
当前细胞为死亡状态时，当周围有3个存活细胞时，该细胞变成存活状态。（模拟繁殖）
*/

void initState()
{
    for (int i = 0; i < VIDEO_SIZE; ++i)
        cell[i] = 0; //0 is dead , 1 is alive
    int x, y;
    byte_out(0x70, 0x2);
    int al = byte_in(0x71);
    byte_out(0x70, 0x0);
    al = al << 8 | byte_in(0x71);
    srand(al);
    int cells = rand() % 1900 + 100;
    for (int i = 0; i < cells; ++i)
    {
        fromIdxToPos(rand() % 2001, &x, &y);
        cell[fromPosToIdx(x, y)] = 1;
    }
}

void nextState()
{
    int dx[] = {0, 0, 1, 1, 1, -1, 1, -1};
    int dy[] = {-1, 1, 0, 0, 1, 1, -1, -1};
    for (int i = 0; i < 25; ++i)
    {
        for (int j = 0; j < 80; ++j)
        {
            int aliveCount = 0, deadCount = 0;
            for (int s = 0; s < 8; ++s)
            {
                int x = i + dx[s], y = j + dy[s];
                if (x >= 0 && x < 25 && y >= 0 && y < 80)
                {
                    //valid position
                    int idx = fromPosToIdx(x, y);
                    if (cell[idx])
                        ++aliveCount;
                    else
                        ++deadCount;
                }
            }
            //统计完毕
            int curIdx = fromPosToIdx(i, j);
            if (cell[curIdx] == 1)
            {
                //alive
                if (aliveCount != 2 && aliveCount != 3)
                    cell[curIdx] = 0;
            }
            else
            {
                //dead
                if (aliveCount == 3)
                    cell[curIdx] = 1;
            }
        }
    }
    renderDisplay();
}

void renderDisplay()
{
    i8 aliveColor = 0x00;
    makeBackgroundColor(&aliveColor, 0, 1, 0);
    i8 deadColor = 0x00;
    makeBackgroundColor(&deadColor, 0, 0, 0);
    for (int x = 0; x < 25; ++x)
        for (int y = 0; y < 80; ++y)
        {
            u32 idx = fromPosToIdx(x, y);
            if (cell[idx] == 0)
                writeVga(idx, ' ', deadColor);
            else
                writeVga(idx, ' ', aliveColor);
        }
}

void refresh_display()
{
    mem_cpy((i8 *)vga, (i8 *)VIDEO_MEMORY, 2 * VIDEO_SIZE);
}
