SRC = $(wildcard *.c)
BIN = $(patsubst %.c, %, $(SRC))

all:$(BIN)

$(BIN):%:%.c
	$(CC) $^ -o $@

clean:
	-@$(RM) $(BIN) .*.sw?
