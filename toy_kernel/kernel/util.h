#define UNITNOP 800
#define UNITNOP2 1700
#define UNITNOP2p 2200
#define UNITNOP3 2650
#define UNITNOP4 3500
#define UNITNOP5 5000
#define UNITNOP6 6500
#define UNITNOP7 8000
#define UNITNOP8 9500
#define UNITNOP9 12000
#define UNITNOP10 14500

int fromPosToIdx(int x, int y);
void fromIdxToPos(int idx, int *x, int *y);
void print(int idx,char *str,char background);
void makeColor(char *src, int r, int g, int b);
void makeBackgroundColor(char *src, int r, int g, int b);
void printWithCursor(int idx, char *str, char background,int waitTime);
void setCursorIdx(int idx);
int getCursorIdx();
void clearScreen();
void nop(int count);