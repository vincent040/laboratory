CC = gcc
CFLAGS = -O0 -Wall

#DEBUG = -g -DDEBUG

ifdef DEBUG
CFLAGS += $(DEBUG)
endif

main:arithmetic.c main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-@$(RM) -rf .*.swp *.o main

.PHONY:clean
