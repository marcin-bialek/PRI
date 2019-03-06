CC := gcc
ARGS := -Wall -Wextra -std=c99 -I include
SRC := $(wildcard src/*.c)
TARGET := bin/Laplace


all: $(SRC)
	mkdir -p bin
	$(CC) $(ARGS) -o $(TARGET) $^ 
