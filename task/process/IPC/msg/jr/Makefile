vpath %.h = $(MYLIB)

#CROSS_COMPILE = arm-linux-gnu-
MYLIB = .
SRC = ${wildcard [^m]*.c}
PRGS := ${patsubst %.c, %, $(SRC)}
CFLAGS ?= -O0 -g -Wall

ifdef CROSS_COMPILE
	CC := $(CROSS_COMPILE)gcc
else
	CC := $(CC)
endif

all:$(PRGS)

$(PRGS):%:%.c mylib.c
	-$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -rf .*.sw? *.o $(PRGS)

.PHONY:clean, all
