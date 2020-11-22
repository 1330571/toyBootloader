# 运行 C 语言程序

> 这篇文章主要学习了[Writing a Bootloader Part2](http://3zanders.co.uk/2017/10/16/writing-a-bootloader2/)和[os-tutorial 8~20](https://github.com/cfenollosa/os-tutorial/blob/master/10-32bit-enter/32bit-switch.asm)

## Environment

安装必须用的交叉编译工具

```shell
port install i386-elf-gcc
port install i386-elf-binutils
brew install i386-elf-gdb
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

## C 语言内联汇编

keyword: \***\*asm\*\***

> asm asm-qualifiers ( AssemblerTemplate  
                   : OutputOperands  
                 [ : InputOperands  
                 [ : Clobbers ] ])  

**volatile** 关键词用于禁止 GCC 的优化器优化掉“无用”的汇编代码，如果提供一些看起来没有效果的代码，应该加上**volatile**

- OutputOperands 被汇编改变的 C 语言变量
- InputOperands 被汇编读取的 C 语言变量

You can see [test_c_asm.c](./test_c_asm.c) for examples to checkout how it works

**tips**

- 无法推断操作数大小的时候需要指定常数的大小前缀,movl,movw,movb,you can see [link](http://www.delorie.com/djgpp/doc/brennan/brennan_att_inline_djgpp.html) for a quick start for GCC inline Asm

- 寻址方面，采用1(%eax)

**符号意义** 
> 
a eax  
b ebx  
c ecx  
d edx  
S esi  
D edi  
I constant value  
q,r   
g  
A

> Now, you might wonder, how to determine how the %n tokens get allocated to the arguments. It's a straightforward first-come-first-served, left-to-right thing, 

## Snippets

[protected_demo](./procted_mode_demo.asm)

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

[GUN Extended-asm](https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html)
