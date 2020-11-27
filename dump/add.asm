
add.o:     file format elf32-i386


Disassembly of section .text:

00000000 <add>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	8b 55 08             	mov    0x8(%ebp),%edx
   6:	8b 45 0c             	mov    0xc(%ebp),%eax
   9:	01 d0                	add    %edx,%eax
   b:	5d                   	pop    %ebp
   c:	c3                   	ret    

0000000d <main>:
   d:	55                   	push   %ebp
   e:	89 e5                	mov    %esp,%ebp
  10:	83 ec 10             	sub    $0x10,%esp
  13:	c7 45 fc 0a 00 00 00 	movl   $0xa,-0x4(%ebp)
  1a:	c7 45 f8 14 00 00 00 	movl   $0x14,-0x8(%ebp)
  21:	ff 75 f8             	pushl  -0x8(%ebp)
  24:	ff 75 fc             	pushl  -0x4(%ebp)
  27:	e8 fc ff ff ff       	call   28 <main+0x1b>
  2c:	83 c4 08             	add    $0x8,%esp
  2f:	89 45 f4             	mov    %eax,-0xc(%ebp)
  32:	90                   	nop
  33:	c9                   	leave  
  34:	c3                   	ret    
