CC = gcc
CFLAGS = -O0 -Wall -g -lpthread

test.elf:main.c thread_pool.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	$(RM) .*.sw? test.elf *.o

.PHONY:all clean
