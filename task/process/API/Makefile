vpath %.h = $(MYLIB)

#CROSS_COMPILE = arm-linux-gnu-
SRC = ${wildcard *.c}
PRGS := ${patsubst %.c, %, $(SRC)} 
CFLAGS ?= -O0 -g -Wall -lpthread

ifdef CROSS_COMPILE
	CC := $(CROSS_COMPILE)gcc
else
	CC := $(CC)
endif

all:$(PRGS)

$(PRGS):%:%.c
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	-@$(RM) -rf .*.sw? *.o $(PRGS)

.PHONY:clean, all
