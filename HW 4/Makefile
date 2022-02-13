CC = clang
CFLAGS = -W -Wextra -Wall -Wpedantic -pedantic
CFLAGS_MEMSAN = -fsanitize=memory -fno-omit-frame-pointer
CFLAGS_UNDEFB = -fsanitize=undefined -fno-sanitize-recover=all
CFLAGS_ADRSAN = -fsanitize=address -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

all:
	$(CC) $(CFLAGS_ADRSAN) $(CFLAGS_UNDEFB) -g demo.c list.c myutilities.c -o demo
	$(CC) $(CFLAGS_MEMSAN) -g demo.c list.c myutilities.c -o demo
	$(CC) $(CFLAGS) -g demo.c list.c myutilities.c -o demo
	valgrind --tool=memcheck -s --leak-check=full ./demo

uic:
	$(CC) $(CFLAGS) -g list.c myutilities.c ui.c -o ui
	./ui	

release:
	$(CC) demo.c myutilities.c list.c -O3 -o demo
	./demo

build:
	$(CC) demo.c -o -O3 demo