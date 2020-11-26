# Toy Boot Loader

简易加载器，汇编语言的课程设计，also inspired by [os-tutorial](https://github.com/cfenollosa/os-tutorial),[osdev](http://osdev.org) and desire for low-level things，旨在对汇编课程上学习过的每种类型的程序简单的尝试一下，加深自己对汇编的理解。

## 什么是 MBR

主引导记录(Main Boot Record)是位于启动磁盘首个扇区的引导程序，**LBA**逻辑块号为 0，或是**CHS**编址方式下的 0 道、0 面、1 号扇区，在 PC 完成自捡(POST)处理后，BIOS 按照预定的启动顺序，读取主引导记录到**0000:7C00H**内存区域，并赚到主引导程序执行。

## 主引导成分分析

1.传统的主引导记录由主引导程(446Bytes)、磁盘分区表(64Bytes)、标记(2Bytes)组成 2.执行步骤为 a)自身腾挪 b)识别活动分区 c)加载引导程序 d)跳转到操作系统的引导程序

- 自身腾挪
- 识别活动分区
- 加载引导程序
- 跳转到引导程序

[HelloWorld BootLoader](./hello_world_loader/readme.md)

[Tiny Makefile Guide](./makefile.md)

## 一些中断

int 0x10

- AH = 14, TTY 格式输出，BH 为页号，AL 为字符的 ASCII 码
- AH = 00, AL 表示显示模式标志

int 0x13

- AH = 2 读扇区

> DL 驱动器号 ES 缓冲区地址段值 BX 缓冲区地址偏移 AL 扇区数 DH 磁头号 CH 低 8 位柱面 CL(高 2 位) 高 2 位柱面号 CL(低 6 位) 扇区号

int 0x16

- AH = 0，输入一个 char，输入到**AL**中
- AH = 1，检测键盘缓冲区是否为空，结果存储在**ZF**中

## 自己编写中断程序

外部中断，CPU 外部引发的中断，如外部设备接口，完全随机方式中断现在程序

- 可屏蔽中断

- 不可屏蔽中断 电源掉电、存储器出错、总线奇偶校验。

- 处理器间中断

- 伪中断

内部中断，由 CPU 内部发生的额某个事件引起的中断称为内部中断，不受中断允许标志控制，不需要外部硬件支持，如果由中断产生的时候，根据 intel i386 manual:

> if a trap is detected in a JMP instruction, the CS and EIP values pushed onto the stack point to the target of the JMP, not to the instruction after the JMP.

### Interrupt Descriptor Table(From i386-manual and os-tutorial)

这个表存储对应**异常**或是**中断**的服务指令位置

> IDT is an array of 8-byte descriptors , contains at most 256 interrupts
>
> LIDT (Load IDT register)

```plain
		IDT LIMIT(15..0) --Select--> Gate For Interrupt #N
IDT BASE 		 (31..0) ----------> Gate For Interrupt #0
```

**IDT Gate Descriptors**

(type: Task Gate, Interrupt Gate, Trap Gate)

- Task Gate -> P DPL 0 0 1 0 1 ......					| Task Switch
- Interrupt Gate-> P DPL 0 1 1 1 0 0 0 0 ......   | Similar to call gate
- Trap Gate-> P DPL 0 1 1 1 1 0 0 0 ......           | Similar to call gate

```plain
31..............16 15 ................... 0
	   NOT USED			 P DPL (Based on type)	
31..............16 15 ................... 0
			SELECTOR						   OFFSET
```

Define as C struct

```c
typedef struct
{
    u16 low_offset; /* Lower 16 bits of handler function address */
    u16 sel;        /* Kernel segment selector */
    u8 always0;
    /* First byte
     * Bit 7: "Interrupt is present" ... P
     * Bits 6-5: Privilege level of caller (0=kernel..3=user) ... DPL
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    u8 flags;
    u16 high_offset; /* Higher 16 bits of handler function address */
} __attribute__((packed)) idt_gate_t;
```

**Procedures**

```plain
						 |-------------------------------------------------> Offset
						 |
Interrupt ID-|--> Trap/Interrupt Gate ---> Segment Descriptor ---> Base
```

use *iret* to return from an interrupt, iret modify the eip while restore eflags
**Stack Layout**

```plain
|	[(2Bytes),Old SS]
| 		[Old Esp]
|		Old Eflags 
|(2Bytes) , Old Cs
|			Old Eip
|		[Error Code]
```

**Error Code Format**

```Plain
UNDEFINED 	SELECTOR INDEX 	TI I EX
```

## Some Information about I/O Ports

- [irq0 => Interrupt Timer](https://wiki.osdev.org/PIT)
  - we could set the 0x43 port as **0x36(0011 1100)**
- 

### CALL & INT(i386 manual)

- CALL

  > PUSH (IP)
  >
  > EIP <- EIP + 16 AND 0000FFFFH

- INT

  > PUSH (FLAGS)
  >
  > IF <- 0
  >
  > TF <- 0
  >
  > PUSH(CS)
  >
  > PUSH(IP)
  >
  > CS <- IDT[中断号 * 4].段选择子
  >
  > IP <- IDT[中断号*4].偏移

- 除法中断 0

## Usage

- 编译所有例子

make all

- 清除所有目标文件

```shell
make clean
```

## tools

- nasm
- qemu
- i386-elf-\_g++

## Hints

**Declaration** type going to be used, but no memory is allocated

**Definition** allocates the memory to variable or function

## reference

[writing a boot loader](http://3zanders.co.uk/2017/10/13/writing-a-bootloader/)

[why-do-boot-loaders-relocate-in-memory](https://stackoverflow.com/questions/1203108/why-do-boot-loaders-relocate-in-memory)

[Interrupt List](http://www.ctyme.com/intr/int.htm)

新概念汇编语言 扬季文 编著 清华大学出版社 ISBN 978-7-302-47634-4
