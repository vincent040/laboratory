#CROSS_COMPILE = arm-none-linux-gnueabi
CC = $(CROSS_COMPILE)gcc

CFLAGS += -Wall
CFLAGS += -I ../lib
CFLAGS += -L ../lib
CFLAGS += -lvnet
CFLAGS += -Wl,-rpath=../lib


ELF = client server

all:$(ELF)

client:client.c 
	$(CC)  $^ -o $@  $(CFLAGS)

server:server.c
	$(CC)  $^ -o $@  $(CFLAGS)

clean:
	$(RM) $(ELF) core *.gz .*.sw?
