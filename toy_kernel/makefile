SOURCES = ${wildcard kernel/*.c ports/*.c}
HEADERS = ${wildcard kernel/*.h ports/*.h}
# 对SOURCES变量集中的所有.c后缀替换为.o后缀
OBJS = ${SOURCES:.c=.o}
# Building Tools
CC = i386-elf-gcc
GDB = i386-elf-gdb
LD = i386-elf-ld
# Building Flags 
FLAG := 
CFLAGS = -ffreestanding -Wall -std=c11 -c
TESTFLAGS = -std=c11 -Wall -O2 ${FLAG} -Werror
# $^ 会去除重复的部分 $< 是一个一个取出来的！

os.bin : boot/bootsect.bin kernel.bin 
	@echo Making The Disk
	cat $^ > os.bin 

kernel.bin : boot/kernel_entry.o ${OBJS} 
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary 

kernel.elf : boot/kernel_entry.o ${OBJS} 
	${LD} -o $@ -Ttext 0x1000 $^ 

%.o : %.c ${HEADERS}
	${CC} ${CFLAGS} $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin : %.asm
	nasm $< -f bin -o $@

.PHONY : run 
run : os.bin
	@echo running The toy kernel ...
	qemu-system-i386 -fda os.bin 

# No Use
# .PHONY : debug
# debug: os.bin kernel.elf
# 	qemu-system-i386 -s -fda os.bin &
# 	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

.PHONY : clean 
clean :
	rm boot/*.o boot/*.bin kernel/*.o ports/*.o kernel.bin os.bin

.PHONY : test
test : 
	cc ${TESTFLAGS} -c test.c -o test.o
	cc ${TESTFLAGS} -c kernel/util.c -o util.o
	cc ${TESTFLAGS} -c ports/ports.c -o ports.o
	cc ${TESTFLAGS} -c libc/mem.c -o mem.o
	cc ${TESTFLAGS} -g test.o util.o ports.o mem.o -o test
	@echo Testing...
	./test 
	@rm test
	@rm *.o