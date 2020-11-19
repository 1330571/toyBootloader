# makefile 的一些 Notes

- @ 表示不显示命令本身，只显示运行结果
- \$@ 表示目标集的变量
- \$< 表示依赖集的变量

## 简易例子，编译**hello_world_loader**下的所有 asm 文件

```makefile

SRC_DIR := ./hello_world_loader
BUILD_DIR := ./hello_world_loader/target
COMPILE_FLAG := -f bin

SRCS := $(wildcard $(SRC_DIR)/*.asm)
BUILD := $(SRCS:$(SRC_DIR)/%.asm=$(BUILD_DIR)/%.bin)

all : hello_chapter

hello_chapter : $(BUILD)

$(BUILD_DIR)/%.bin: $(SRC_DIR)/%.asm
	@echo + nasm $<
	@mkdir -p $(BUILD_DIR)
	@nasm $(COMPILE_FLAG) $< -o $@


.PHONY : clean
clean:
	-rm -rf $(BUILD_DIR)/*.bin

```
