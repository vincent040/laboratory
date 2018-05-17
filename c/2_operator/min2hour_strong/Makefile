#CROSS_COMPILE = arm-linux-gnu-

SRC = ${wildcard *.c}
CFLAGS ?= -O0 -g -Wall

ifdef CROSS_COMPILE
	CC := $(CROSS_COMPILE)gcc
else
	CC := $(CC)
endif

main:$(SRC)
	- $(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf .*.sw? *.o main

.PHONY:clean, all
