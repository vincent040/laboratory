CFLAGS += -L.
CFLAGS += -I.
CFLAGS += -lsqlite3
CFLAGS += -lpthread
CFLAGS += -ldl
CFLAGS += -Wl,-rpath=.

demo:demo.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	-@$(RM) demo *.o
