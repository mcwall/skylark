SOURCE_DIR=src
OUTPUT_DIR=bin

SOURCE_FILES = $(SOURCE_DIR)/mem.cpp $(SOURCE_DIR)/cpu.cpp $(SOURCE_DIR)/display.cpp $(SOURCE_DIR)/renderer.cpp $(SOURCE_DIR)/loader.cpp $(SOURCE_DIR)/skylark.cpp

OUT=$(OUTPUT_DIR)/skylark

CC = g++ -g
CC_OPTS = -std=c++11 -lSDL2

all: Build

Build:
	$(CC) $(SOURCE_FILES) -o $(OUT) $(CC_OPTS)

clean:
	rm -rf $(SOURCE_DIR)/*

run: Build
	$(OUT)