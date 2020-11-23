default : all

.PHONY : all
all:
	cd hello_world_loader && make hello_chapter
	cd toy_kernel && make os.bin
.PHONY : clean
clean:
	cd hello_world_loader && make clean
	cd toy_kernel && make clean

.PHONY : run
run:
	cd toy_kernel && make run
