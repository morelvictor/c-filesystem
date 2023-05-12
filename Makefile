.PHONY: build run clean deps

SRC_DIR = src
BUILD_DIR = .out
OBJ = main.o node.o node_list.o parser.o path.o cst.o

build: $(OBJ)
	gcc -g -Wall -o main $(OBJ:%=$(BUILD_DIR)/%)

run: build
	./main

test: build
	./main tests.txt

clean:
	rm -f $(BUILD_DIR)/*.o main

deps:
	gcc -MM src/*.c

leaks: build
	leaks -atExit --list -- ./main tests.txt

%.o: $(SRC_DIR)/%.c
	-mkdir -p $(BUILD_DIR)
	gcc -g -Wall -o $(BUILD_DIR)/$@ -c $<

