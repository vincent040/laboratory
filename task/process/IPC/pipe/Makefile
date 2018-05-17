PRGS = $(patsubst %.c, %, $(wildcard *.c))
#DEBUG = -O0 -Wall -g 
CFLAGS += $(DEBUG)

all:$(PRGS)

$(PRGS):%:%.c
	- $(CC) $(CFLAGS) -o $@ $^

clean:
	- $(RM) $(PRGS) .*.sw? *.o

.PHONY:clean all
