all:client server

client:client.c
	gcc $^ -o $@ -lnetlib

server:server.c
	gcc $^ -o $@ -lnetlib

clean:
	rm -rf client server
