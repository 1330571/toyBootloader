
call_test:     file format elf32-i386


Disassembly of section .text:

00000000 <main>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 10             	sub    $0x10,%esp
   6:	c7 45 fc 00 00 10 00 	movl   $0x100000,-0x4(%ebp)
   d:	8b 45 fc             	mov    -0x4(%ebp),%eax
  10:	8b 00                	mov    (%eax),%eax
  12:	ff d0                	call   *%eax
  14:	90                   	nop
  15:	c9                   	leave  
  16:	c3                   	ret    
