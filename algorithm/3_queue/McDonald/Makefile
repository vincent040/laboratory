CC = gcc
CFLAGS = -O0 -g -Wall -lpthread

McDonald:queue.c McDonald.c 
	- $(CC) -o $@ $^ $(CFLAGS)

.PHONY:clean
clean:
	- $(RM) -rf .*.swp *.o McDonald
