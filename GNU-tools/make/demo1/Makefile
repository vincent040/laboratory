SRC = ${wildcard *.c}
#SRC = a.c b.c c.c d.c ....
BIN = ${patsubst %.c, %, $(SRC)}
#BIN = a b c d .....

#CFLAGS = -Wall -O0 -g

CROSSTOOLS = arm-linux-

ifdef CROSSTOOLS
	CC = $(CROSSTOOLS)gcc
else
	CC = gcc
endif

#all:$(BIN)
$(BIN):$(SRC)

#$(BIN):%:%.c
#	$(CC) $^ -o $@ $(CFLAGS)

clean:
	$(RM) $(BIN)

.PHONY:all clean
