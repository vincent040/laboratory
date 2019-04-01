PRGS = ${patsubst %.c, %, ${wildcard *.c}}
DEBUG := -O0 -g -Wall
CFLAGS += $(DEBUG)

all:$(PRGS)

$(PRGS):%:%.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) -rf .*.sw? *.o $(PRGS)

.PHONY:clean
