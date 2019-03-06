CC := gcc
ARGS := -std=c99 -Wall -Wextra -I include
SRC := $(wildcard src/*.c)
TARGET := bin/Liga


all: $(SRC)
	mkdir -p bin
	$(CC) $(ARGS) -o $(TARGET) $^ 
