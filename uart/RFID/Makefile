SRC = $(wildcard *.c)
BIN = $(SRC:%.c=%)

all:$(BIN)

CROSS = arm-none-linux-gnueabi-
CC = $(CROSS)gcc

$(BIN):%:%.c
	   $(CC) $^ -o $@ $(CPPFLAGS)

clean:
	$(RM) $(BIN)
