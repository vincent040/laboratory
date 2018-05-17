vpath %.h = $(MYLIB)

#CROSS_COMPILE = arm-linux-gnu-
SRC = ${wildcard *.c}
PRGS := ${filter-out sem_com, ${patsubst %.c, %, $(SRC)}} 
CFLAGS ?= -O0 -g -Wall

ifdef CROSS_COMPILE
	CC := $(CROSS_COMPILE)gcc
else
	CC := $(CC)
endif

all:$(PRGS)

$(PRGS):%:$(SRC)
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf .*.sw? *.o $(PRGS)

.PHONY:clean, all
