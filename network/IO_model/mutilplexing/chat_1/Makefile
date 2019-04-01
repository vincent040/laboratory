BIN = ${filter-out wrapper, ${patsubst %.c, %, ${wildcard *.c}}}

all:$(BIN)

qq_srv:qq_srv.c wrapper.c
	gcc $^ -o $@ -lnetlib

qq_cli:qq_cli.c wrapper.c
	gcc $^ -o $@ -lnetlib

clean:
	rm $(BIN) .*.sw? -f
