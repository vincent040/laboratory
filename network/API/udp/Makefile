SRC = ${wildcard *.c}
BIN = ${patsubst %.c, %, $(SRC)}

all:$(BIN)

$(BIN):%:%.c
	$(CC) -o $@ $^ $(CFLAGS) -lnetlib

clean:
	$(RM) $(BIN) .*.sw?
