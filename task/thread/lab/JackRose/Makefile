SRC = $(wildcard *.c)
BIN = $(patsubst %.c, %, $(SRC))

all:$(BIN)

$(BIN):%:%.c
	$(CC) -o $@ $^ $(CFLAGS) -lpthread


.PHONY:clean
clean:
	@$(RM) $(BIN) .*.sw? *.o 
