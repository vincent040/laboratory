vpath %.h = $(MYLIB)

#CROSS_COMPILE = arm-linux-gnu-
MYLIB = /home/seton/example
SRC = ${wildcard *.c}
PRGS := ${patsubst %.c, %, $(SRC)} 
CFLAGS ?= -O0 -g -Wall

ifdef CROSS_COMPILE
	CC := $(CROSS_COMPILE)gcc
else
	CC := $(CC)
endif

all:$(PRGS)

$(PRGS):%:%.c
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf .*.sw? *.o $(PRGS)

.PHONY:clean, all
