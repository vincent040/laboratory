SRC = ${wildcard *.c}
BIN = ${patsubst %.c, %, $(SRC)}

CFLAGS = -g -Wall

all:$(BIN)

$(BIN):%:%.c
	$(CC) $(CFLAGS) -o $@ $^ -lnetlib

install:
	$(MAKE) -C ../../netlib

clean:
	$(RM) $(BIN) .*.sw?

.PHONY:all clean
