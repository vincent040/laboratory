CC = gcc
CFLAGS = -O0 -Wall -g -lpthread

copy.elf:copy.c thread_pool.c
	$(CC) $^ -o $@ $(CFLAGS) -DNDEBUG

debug.elf:copy.c thread_pool.c
	$(CC) $^ -o $@ $(CFLAGS) -DDEBUG

clean:
	$(RM) .*.sw? copy.elf debug.elf *.o bk -rf

.PHONY:all clean
