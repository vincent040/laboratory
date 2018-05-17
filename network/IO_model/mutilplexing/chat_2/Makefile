BIN = $(filter-out wrap, $(patsubst %.c, %, $(wildcard *.c)))

all:$(BIN)

server:server.c wrap.c
	$(CC) $^ -o $@ -lvnet -Wall

client:client.c wrap.c
	$(CC) $^ -o $@ -lvnet -Wall

clean:
	-@$(RM) $(BIN) .*.sw? -f
