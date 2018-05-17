SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

ifdef TOOLCHAIN
	CC = $(TOOLCHAIN)
else
	CC = gcc
endif

image:$(OBJ)
ifeq ($(CC),gcc)
	$(CC) $(OBJ) -o image -lgcc
else
	$(CC) $(OBJ) -o image
endif

$(OBJ):%.o:%.c
	$(CC) $^ -o $@ -c

clean:
	$(RM) $(OBJ) image

.PHONY:clean
