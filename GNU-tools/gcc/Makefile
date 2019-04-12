#CFLAGS = -Wall -g -O0
CC = gcc
cc1_PATH = /usr/lib/gcc/i486-linux-gnu/4.4

STUFF = hello.i hello.s hello.o hello

all:$(STUFF)

hello.i:hello.c
	@echo "====================preprocessing===================="
	$(CC) $(CFLAGS) -o $@ $^ -E
	cpp -o $@ $^

hello.s:hello.c
	@echo "======================compiling======================"
	$(CC) $(CFLAGS) -o $@ $^ -S
	$(cc1_PATH)/cc1 -o $@ $^

hello.o:hello.s
	@echo "=====================assembling======================"
	$(CC) $(CFLAGS) -o $@ $^ -c
	as -o $@ $^

hello:hello.o
	@echo "======================linking========================"
	$(CC) $(CFLAGS) -o $@ $^
	ld -static /usr/lib/crt1.o /usr/lib/crti.o /usr/lib/gcc/i486-linux-gnu/4.4/crtbeginT.o -L/usr/lib/gcc/i486-linux-gnu/4.4 -L/usr/lib -L/lib hello.o --start-group -lgcc -lgcc_eh -lc --end-group /usr/lib/gcc/i486-linux-gnu/4.4/crtend.o /usr/lib/crtn.o -o $@

.PHONY:clean
clean:
	@-$(RM) -rf $(STUFF) .*.sw?
	@clear
