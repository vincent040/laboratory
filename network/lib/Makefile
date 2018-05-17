SRC = ${wildcard *.c}
OBJ = ${patsubst %.c, %.o, $(SRC)}

CFLAGS = -c -Wall -fPIC
LIBFLAGS = -shared -fPIC

#CROSS = arm-none-linux-gnueabi-
CC = $(CROSS)gcc

all:$(OBJ)

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) -o $@ $^

install:
	$(CC) $(LIBFLAGS) -o libvnet.so $(OBJ)

clean:
	$(RM) $(OBJ) libvnet.so .*.sw?

.PHONY:all clean
