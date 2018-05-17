CFLAGS = -O0 -Wall -ggdb -lpthread

buffer_mutexinit:main.c buffer_mutexinit.c
	- $(CC) -o $@ $^ $(CFLAGS)
clean:
	@ - $(RM) .*.sw? *.o buffer_mutexinit

.PHONY:clean
