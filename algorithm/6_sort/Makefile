SRC = $(wildcard *.c)
ELF = $(SRC:%.c=%.elf)

#CROSS = arm-none-linux-gnueabi-
CC = $(CROSS)gcc

LDFLAGS += -lm

all:$(ELF)

$(ELF):%.elf:%.c
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	$(RM) $(ELF)
