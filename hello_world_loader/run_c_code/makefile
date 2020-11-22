dafault : all

.PHONY : all
all : protected_mode_demo.bin test_c_asm

protected_mode_demo.bin : protected_mode_demo.asm
	nasm protected_mode_demo.asm -f bin -o protected_mode_demo.bin

test_c_asm : test_c_asm.c
	cc test_c_asm.c -o test_c_asm -Wall -std=c11
