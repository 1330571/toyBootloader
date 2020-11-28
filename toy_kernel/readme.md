# 一个破烂kernel

## 函数

### util.h

```c
//将str存储为n的16进制表示
void int_to_hex_ascii(int n, char str[]); 
//将str存储为n的10进制表示
void int_to_ascii(int n, char str[]);
//字符串长度
int str_len(char *str);
//char数组转int
int charToInt(char *str);
//根据x，y坐标计算TTY模式下的索引值
int fromPosToIdx(int x, int y);
//根据TTY模式下的索引值计算x，y坐标
void fromIdxToPos(int idx, int *x, int *y);
//弃用，根据背景颜色输出str字符串到idx中
void print(int idx, char *str, char background);
//弃用，将src的r，g，b位单独赋值
void makeColor(char *src, int r, int g, int b);
//弃用，将src的背景r，g，b位单独赋值
void makeBackgroundColor(char *src, int r, int g, int b);
//将str输出到idx，waitTime是打印时的等待时间，实现打字机的效果
void printWithCursor(int idx, char *str, char background, int waitTime);
//利用I/O设置光标
void setCursorIdx(int idx);
//利用I/O获取光标
int getCursorIdx();
//清除屏幕
void clearScreen();
//无意义的等待，切勿开编译优化否则这代码直接被优化没了
void nop(int count);
//等待一个按键，未实现
void waitForKey();
//随机数，从OS-dev 复制的
int rand(void);
//随机数，从OS-dev 复制的
void srand(unsigned int seed);
//BCD码转换为U8类型
unsigned char bcdToInt(unsigned char byte);
//看名字
void bcdTo2Bytes(unsigned char byte, char *high_byte, char *low_byte);
//根据光标位置滚一行屏幕
void scrollOneLine();
//输出一个字符，不能输出'\n'，需指定索引
void printChar(int idx, char str, char background);
//输出一个字符，不能输出'\n'
void putChar(char data, char color);
//输出一个字符串，可以有'\n'，不需要指定索引
void putChars(char *data, char color);
//回退一个字符，不怎么靠谱，可以一直回退，没有Guard
void backOneChar();
//没啥用的函数
int add_value(int a,int b);
//输出一个字符画用的，碰到'\n'不返回首行
void special_put_chars(int x, int y, char *data, char color);
```

### life.h

```c
//重绘屏幕
void refresh_display();
//直接写VGA显存
void writeVga(u32 idx, u8 data, u8 attr);
//生命游戏推进一个Frame
void nextState();
//初始化生命游戏
void initState();
```

### fakefs.h

```c
//装载文件，其实就是memcpy
void load_file(u8 *src, u8 *dst, u32 len);
//没啥用，就是jmp
void execute_file_by_jmp(u32 addr);
//也没啥用，就是call
void execute_file_by_call(u32 addr);
//扫描内存，根据宏定义的一个区间扫
void build_up_mem_map();
```

### mem.h

```c
//memcpy
void mem_cpy(char *src, char *dst, int len);
//strcmp
char mem_equ(char *src, char *src2);
//strcmp，但是src2只要是str的前缀就可以
char mem_equ_ctl_by_src2(char *src, char *src2);
//strcmp，不看大小写
char mem_equ_ignore_case(char *src, char *src2);
```

### string.h

```c
//data放到s后面
void append(char s[], char data);
//删除一个字符
void delete (char s[]);
//
int cmpOneWord(char *word, char *str);
//转换为小写
char to_lower(char data);
```

### keyboard.h

```c
//分配键盘回调函数
void init_keyboard();
void keyboard_callback(registers_t regs);
//清空键盘缓冲区，和键盘的状态
void reset();
```

### timer.h

```c
//分配timer的回调函数
void init_timer(unsigned int frequency);
//系统执行到现在的toy unit数
extern u32 booting_tick;
```

## Shell模式

- hello 输出 “你好，代码人，代码人更是人上人” 的梗
- clear 清除屏幕
- whoami 输出你是管理员
- time 输出系统运行的toy unit秒，具体多少这个单位时间是多少毫秒我也不知道
- quit 输出下次再见，然后死循环
- ls 列出所有的可执行文件
- help + 可执行文件名 输出执行文件在磁盘中定义的DESCRIPTION信息
- run + 可执行文件名 执行可执行文件

## 可执行文件格式

ABCDE 是可执行文件头

然后到字符串截断为止是文件名

再到字符串截断为止是文件的描述信息

如`db 'ABCDE','Logo',0,'See the Logo for this toy OS',0`

就是可执行文件Logo，使用`run logo`运行

使用`help logo`会显示`see the logo for this toy os`

所有执行文件必须以下述格式编写，否则可能会出问题，ret必须要有，不然回不去。

```assembly
pusha
; main code
popa
ret
```

## Usage

```shell
make run
```

## 中断改写

**int 20** 打字机模式输出一串字符串，ebx 表示地址,ah 表示输出字体的颜色，cl,ch 分表表示 y 轴和 x 轴的位置

**int 21** 清除屏幕

**int 22** 输入一个整型数字到 eax 中，按回车触发,不允许输入重复数字(不知道怎么解决)，同时读取结果会返回到0x100000地址，使用请通过下述规则

```assembly
addr equ 0x100000

xor eax, eax
int 22 ; 获取数字输入   
mov eax,[addr]
```

**int 23** 按键下一步

**int 24** 根据光标输出，ebx表示地址，ah 表示输出字体的颜色

**int 25** 输出eax的数值，bh表示颜色值

**int 26** 等待eax个单位(toy unit，具体时间我也不知道)

**int 27** 不等待输出，设置和20一样，专门用于输出第三个工作程序这样的字符画

## 注意

所有可执行文件地址必须固定，文件系统是一个假文件系统，执行时并不会装载程序到任何特定的地址执行，所以所有的偏移什么的请妥善处理，从0x7E00开始就是工作程序的位置，在哪就偏移多少，否则会出问题，建议全部写在`bootsect.asm`中

## 工作程序

1.用C语言写的生命游戏 开机就能看见

2.Logo 以打字机效果画一个非常丑的字符画出来

3.计算快递价格，规则非常简单

4.一个字符小人跳来跳去

