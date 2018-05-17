CFLAGS := -O0 -Wall $(ABC)
DEBUG ?= -g
CFLAGS += $(DEBUG)

SRC = ${wildcard *.c}
PRGS = ${patsubst %.c, %, $(SRC)}

all:$(PRGS)

$(PRGS):%:%.c
	- $(CC) $(CFLAGS) -o $@ $^ -lvsort -lvlist

clean:
	- $(RM) -f $(PRGS) .*.sw? *.o

.PHONY:clean all
