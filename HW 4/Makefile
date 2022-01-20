# valgrind --tool=memcheck ./intal.out
CFLAGS = -W -Wextra -Wall -Wpedantic -pedantic
CFLAGS_MEMSAN = -fsanitize=memory -fno-omit-frame-pointer
CFLAGS_UNDEFB = -fsanitize=undefined
CFLAGS_ADRSAN = -fsanitize=address

CC = clang

all:
	$(CC) $(CFLAGS_ADRSAN) -g main.c -o main
	$(CC) $(CFLAGS_UNDEFB) -g main.c -o main
	$(CC) $(CFLAGS_MEMSAN) -g main.c -o main
	$(CC) $(CFLAGS) -g main.c -o main
	valgrind --tool=memcheck -s --leak-check=full ./main
	./main

raw:
	$(CC) $(CFLAGS) main.c -o -O3 main
	./main

build:
	$(CC) main.c -o -O3 main