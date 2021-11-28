CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -g -lm
TARGET = main

main: build
	@echo "Run by typing ./main.o"

build:
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET).o

test:
	$(CC) $(CFLAGS) -D TEST=_ $(TARGET).c -o $(TARGET).o
	./$(TARGET).o
