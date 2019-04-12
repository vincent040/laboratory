PRGS = ${patsubst %.c, %, ${wildcard *.c}}
DEBUG = -O0 -g -Wall
CFLAGS += $(DEBUG)

#CROSS_COMPILE = arm-linux-gnu-
ifdef CROSS_COMPILE
	CC = $(CROSS_COMPILE)gcc
else
	CC = gcc
endif

all:$(PRGS)

$(PRGS):%:%.c
	- $(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf main $(PRGS) .*.swp

.PHONY:clean install
