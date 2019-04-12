PRGS = ${filter-out all_in_all, ${patsubst %.c, %, ${wildcard *.c}}}
CC = gcc
CFLAGS = -O0 -g -Wall

all:$(PRGS)

$(PRGS):%:%.c
	- $(CC) $(CFLAGS) -o $@ $^

clean:
	- $(RM) -rf .*.swp *.o $(PRGS)

.PHONY:clean all
