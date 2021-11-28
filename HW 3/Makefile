CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -g -lm
TARGET = main

main: main.c
	./$(TARGET).o

main.c:
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET).o

test:
	$(CC) $(CFLAGS) -D TEST=_ $(TARGET).c -o $(TARGET).o
	./$(TARGET).o
