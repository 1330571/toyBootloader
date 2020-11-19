SRC_DIR := ./
BUILD_DIR := ./target
COMPILE_FLAG := -f bin

SRCS := $(wildcard $(SRC_DIR)/*.asm)
BUILD := $(SRCS:$(SRC_DIR)/%.asm=$(BUILD_DIR)/%.bin)

hello_chapter : $(BUILD)

$(BUILD_DIR)/%.bin: $(SRC_DIR)/%.asm
	@echo + nasm $< 
	@mkdir -p $(BUILD_DIR)
	@nasm $(COMPILE_FLAG) $< -o $@ 
	
.PHONY : clean
clean:
	-rm -rf $(BUILD_DIR)/*.bin