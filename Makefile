
SRC_DIR = src
BUILD_DIR = .out

lib.o: $(SRC_DIR)/lib.c
	mkdir -p $(BUILD_DIR); gcc -Wall -o $(BUILD_DIR)/lib.o -c $(SRC_DIR)/lib.c

