.PHONY: build run clean deps

SRC_DIR = src
BUILD_DIR = .out

build: main.o node.o parser.o path.o
	gcc -o main .out/main.o .out/node.o .out/parser.o .out/path.o

run: build
	./main

test: build
	./main instr.txt

clean:
	rm -f $(BUILD_DIR)/*.o main

deps:
	gcc -MM src/*.c

leaks: build
	leaks -atExit -- ./main instr.txt

%.o: $(SRC_DIR)/%.c
	-mkdir -p $(BUILD_DIR)
	gcc -Wall -o $(BUILD_DIR)/$@ -c $<

