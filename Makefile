SOURCE_DIR=src
OUTPUT_DIR=bin

SOURCE_FILES=$(SOURCE_DIR)/main.cpp

OUT=$(OUTPUT_DIR)/skylark

CC=g++
CC_OPTS=-std=c++11 -lSDL2

all: Build

Build:
	$(CC) $(SOURCE_FILES) -o $(OUT) $(CC_OPTS)

clean:
	rm -rf $(OUTPUT_DIR)/*

run: Build
	$(OUT)