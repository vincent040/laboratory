CC = arm-none-linux-gnueabi-gcc

ELF = uart.elf

all:$(ELF)

$(ELF):%.elf:%.c
	$(CC) $^ -o $@ -lpthread

clean:
	$(RM) $(ELF)
