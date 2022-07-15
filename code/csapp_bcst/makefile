CC = /usr/bin/gcc-9
CFLAGS = -Wall -g -O2 -Werror -std=gnu99 -Wno-unused-function

EXE_HARDWARE = exe_hardware

SRC_DIR = ./src

# debug
COMMON = 	$(SRC_DIR)/common/convert.c \
			$(SRC_DIR)/common/print.c

# hardware
CPU = 	$(SRC_DIR)/hardware/cpu/isa.c \
		$(SRC_DIR)/hardware/cpu/mmu.c

MEMORY = $(SRC_DIR)/hardware/memory/dram.c

# main
MAIN_HARDWARE = $(SRC_DIR)/main_hardware.c

.PHONY: hardware
hardware:
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(COMMON) $(CPU) $(MEMORY) $(MAIN_HARDWARE) -o $(EXE_HARDWARE)

run:
	./$(EXE_HARDWARE)

clean:
	rm -f *.o *~ $(EXE_HARDWARE)