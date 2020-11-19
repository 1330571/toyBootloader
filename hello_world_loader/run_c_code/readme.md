# 运行 C 语言程序

> 这篇文章主要学习了[Writing a Bootloader Part2](http://3zanders.co.uk/2017/10/16/writing-a-bootloader2/)和[os-tutorial 8~10](https://github.com/cfenollosa/os-tutorial/blob/master/10-32bit-enter/32bit-switch.asm)

## Environment

安装必须用的交叉编译工具

```shell
port install i386-elf-gcc
port install i386-elf-binutils
```

## 如何进入保护模式

在 16 位实模式下，我们只可以使用 1MB 的寻址空间，可以使用 A20 总线来开启第 21 位的寻址空间。

### GDT

Work In Progress...

## ELF 文件格式

ELF Header
Program header table
.text
.rotate
...
.data
Section header table
See **reference** for further information

## Snippets

[protected_demo](./procted_mode_demo.asm) **Work In Progress**

## Reference

[os-tutorial 10-32bit-enter](https://github.com/cfenollosa/os-tutorial/blob/master/10-32bit-enter/32bit-switch.asm)

[Writing a Bootloader Part2](http://3zanders.co.uk/2017/10/16/writing-a-bootloader2/)

[wiki](https://en.wikipedia.org/wiki/A20_line)

[wiki dev](https://wiki.osdev.org/A20_Line)

[wiki int 0x10](https://zh.wikipedia.org/wiki/INT_10H)

[wiki How do i set a graphics mode](https://wiki.osdev.org/How_do_I_set_a_graphics_mode)

[wiki VGA text mode](https://en.wikipedia.org/wiki/VGA_text_mode)

[Global_Descriptor_Table](https://wiki.osdev.org/Global_Descriptor_Table)

[understanding ELF format file](https://linuxhint.com/understanding_elf_file_format/)