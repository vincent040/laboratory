SRC = ${wildcard *.c}
BIN = ${patsubst %.c, %, $(SRC)}

CFLAGS = -g -Wall

all:$(BIN)

$(BIN):%:%.c
	$(CC) $(CFLAGS) -o $@ $^ -lnetlib

clean:
	$(RM) $(BIN) .*.sw?

.PHONY:all clean
