CFLAGS = -O0 -Wall -ggdb -lpthread

buffer_mutexinit_boundary:main.c buffer_mutexinit_boundary.c
	- $(CC) -o $@ $^ $(CFLAGS)

clean:
	@ - $(RM) .*.sw? *.o buffer_mutexinit_boundary

.PHONY:clean
