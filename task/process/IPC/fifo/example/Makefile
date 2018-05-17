PRGS = ${filter-out restart, ${patsubst %.c, %, ${wildcard *.c}}}
DEBUG := -O0 -g -Wall
CFLAGS += $(DEBUG)

all:$(PRGS)

$(PRGS):%:%.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) -rf .*.sw? *.o $(PRGS) p

.PHONY:clean
