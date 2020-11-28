# 一个显示生命游戏的例子

## 函数

```c
//int转char数组
void int_to_ascii(int n, char str[]);
//获取数组长度
int str_len(char *str);
//char转换为int
int charToInt(char *str);
//根据x,y坐标计算VGA index
int fromPosToIdx(int x, int y);
//根据VGA下标计算x，y坐标
void fromIdxToPos(int idx, int *x, int *y);
//输出，根据下标，数组，颜色
void print(int idx, char *str, char background);
//给字体颜色赋值
void makeColor(char *src, int r, int g, int b);
//给背景颜色赋值
void makeBackgroundColor(char *src, int r, int g, int b);
//一边输出一边控制cursor
void printWithCursor(int idx, char *str, char background, int waitTime);
//直接设置cursor
void setCursorIdx(int idx);
//获取cursor索引，记得除以2
int getCursorIdx();
//清屏
void clearScreen();
//无意义等待，切勿开启C优化 否则无效
void nop(int count);
//not implemented
void waitForKey();
//生成随机数
int rand(void);
//设置随机数种子
void srand(unsigned int seed);
//bcd码转int
unsigned char bcdToInt(unsigned char byte);
//获取bcd码的俩个16位表示
void bcdTo2Bytes(unsigned char byte, char *high_byte, char *low_byte);
//滚屏
void scrollOneLine();
//输出一个字符，需要指示索引
void printChar(int idx, char str, char background);
//输出一个字符
void putChar(char data, char color);
//输出一堆字符
void putChars(char *data, char color);
```

## Usage

```shell
make run
```

## 中断改写

**int 20** 打字机模式输出一串字符串，ebx 表示地址,ah 表示输出字体的颜色，cl,ch 分表表示 y 轴和 x 轴的位置

**int 21** 清除屏幕

**int 22** 输入一个整型数字到 eax 中，按回车触发,不允许输入重复数字(不知道怎么解决)

**int 23** 按键下一步

**int 24** 往后输出，ebx表示地址，ah 表示输出字体的颜色

**int 25** 输出eax的数值，bh表示颜色值

**int 26** 等待eax个单位(toy unit，具体时间我也不知道)

**int 27** 不等待输出，设置和20一样

