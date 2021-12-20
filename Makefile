SWAP_SIZE_GB=20
MAX_MEMORY_SIZE=30
SWAP_FILE=./swap
MASSIF_OUT=./test.out
MS_OUT=./memory.log

all: clean main massif
main: main.c
	-@gcc -O3 main.c -o main
massif: main
	-@printf "\e[?25l"
	-@valgrind --tool=massif --massif-out-file=${MASSIF_OUT} ./main ${MAX_MEMORY_SIZE}
	-@ms_print ${MASSIF_OUT} > ${MS_OUT}
	-@printf "\e[?25h"
swap:
	fallocate -l ${SWAP_SIZE_GB}G ${SWAP_FILE}
	dd if=/dev/zero of=${SWAP_FILE} bs=1024 count=${SWAP_SIZE_GB}M
	chmod 600 ${SWAP_FILE}
	mkswap ${SWAP_FILE}
	swapon ${SWAP_FILE}
swapoff: clean
	-swapoff -a
	-rm -rf ${SWAP_FILE}
clean:
	-@rm -rf main *.log *.out
