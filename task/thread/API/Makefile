SRC = $(wildcard *.c)
BIN = $(patsubst %.c, %, $(SRC))

CFLAGS = -lpthread

all:$(BIN)

$(BIN):%:%.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(BIN)

.PHONY:all clean
