.PHONY: build run clean deps

SRC_DIR = src
BUILD_DIR = .out

build: main.o node.o parser.o path.o
	gcc -o main $(BUILD_DIR)/$<

run: build
	./main

clean:
	rm -f $(BUILD_DIR)/*.o main

deps:
	gcc -MM src/*.c

%.o: $(SRC_DIR)/%.c
	-mkdir -p $(BUILD_DIR)
	gcc -Wall -o $(BUILD_DIR)/$@ -c $<

