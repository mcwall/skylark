SOURCE_DIR=src
OUTPUT_DIR=bin

SOURCE_FILES = $(SOURCE_DIR)/keyboard.cpp $(SOURCE_DIR)/timer.cpp $(SOURCE_DIR)/mem.cpp $(SOURCE_DIR)/font.cpp $(SOURCE_DIR)/frame.cpp $(SOURCE_DIR)/cpu.cpp $(SOURCE_DIR)/renderer.cpp $(SOURCE_DIR)/loader.cpp $(SOURCE_DIR)/skylark.cpp

OUT=$(OUTPUT_DIR)/skylark

CC = g++ -g
CC_OPTS = -std=c++11 -lSDL2

all: Build

Build:
	$(CC) $(SOURCE_FILES) -o $(OUT) $(CC_OPTS)

clean:
	rm -rf $(OUTPUT_DIR)/*

run: Build
	$(OUT)