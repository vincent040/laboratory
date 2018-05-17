CFLAGS := -g -ggdb  -Wall
PRGS := ${patsubst %.c, %, ${wildcard *.c}}

#CROSS_COMPILE = arm-linux-gnu-
ifdef CROSS_COMPILE
	CC := $(CROSS_COMPILE)gcc
else
	CC = gcc
endif

all:$(PRGS)

$(PRGS)%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY: dist clean
clean:
	rm -rf debugme struct callstk core *.gz a.out

dist: clean
	tar czf debugging_example.tar.gz *.c Makefile
