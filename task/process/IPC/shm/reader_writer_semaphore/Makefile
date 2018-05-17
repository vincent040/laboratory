PRGS = $(filter-out wrap, $(patsubst %.c, %, $(wildcard *.c)))
DEBUG := -O0 -g -Wall
CFLAGS += $(DEBUG)

all:$(PRGS)

$(PRGS):%:%.c wrap.c
	gcc -o $@ $^ $(CFLAGS) -lpthread

clean:
	$(RM) -rf .*.sw? *.o $(PRGS)

.PHONY:clean
