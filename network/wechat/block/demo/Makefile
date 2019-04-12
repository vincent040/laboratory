CPPFLAGS = -I.

LDFLAGS += -L.
LDFLAGS += -lpthread

all:server.elf client.elf

server.elf:server.c wrap.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

client.elf:client.c wrap.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) server.elf client.elf
