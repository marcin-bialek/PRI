CC := gcc
ARGS := -Wall -Wextra
SRC := $(wildcard src/*.c)
TARGET := bin/BinToDec


all: $(SRC)
	mkdir -p bin
	$(CC) $(ARGS) -o $(TARGET) $^ 
