# Hello World Boot Loader

## 简易 NASM 指令介绍

- [名称] DB 字节数据项
- [名称] DW 单字数据项
- [名称] DD 双字数据项

- [名称] RESB 预留字节存储单元的数量
- [名称] RESW 预留单字存储单元的数量
- [名称] RESD 预留双字存储单元的数量

- TIMES 次数 [伪]指令
- 符号名 EQU 数值表达式
- $ $\$ 当前指令的相对偏移 当前段处在整个程序中的相对偏移

- org 给出假设的起始偏移
- bits 16[32] 默认的操作数尺寸是 8 16[32]位，以及寻址方式的设定
- hlt 暂停，复位信号、非屏蔽中断、可屏蔽中断时恢复，cli 可以让暂停状态不响应可屏蔽中断

## 寄存器

> 通用寄存器 AX,BX,CX,DX,SP,BP,SI,DI

> 段寄存器 CS,DS(数据段),SS(堆栈段),ES FS,GS

## 一些简单的汇编程序演示

如何编译及运行？

```shell
nasm xxx.asm -f bin -o xxx.bin
qemu-system-i386 -fda xxx.bin
```

- [Hello World](./boot_hello_world.asm) 一个简单的输出HELLO WORLD程序
- [Simple Input And Output](./boot_key_receiver.asm) 一个简单的输出你按的键盘的程序
- [More Than 512 Bits](./boot_load_sector.asm) 一个简单的读取第二扇区的程序
- [Move Myself to another](./boot_move_myself.asm) 将自己腾挪到0x600区域，可以通过qemu monitor的memsave函数查看内存情况
- [Custom Interrupt](./boot_custom_interrupt.asm) 一个简单的除法中断程序
- [Run C Code](./run_c_code/readme.md) **Work In Progress**
