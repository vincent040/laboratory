SRC = ${wildcard *.c}
OBJ = ${patsubst %.c, %.o, $(SRC)}

LIB_PATH = /lib
HEADER_PATH = /usr/include

libvqueue.a:$(OBJ)
	$(AR) crs $@ $^

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) -o $@ $^ -c

install:
	cp libvqueue.a $(LIB_PATH)
	cp head4queue.h $(HEADER_PATH)

clean:
	$(RM) .*.sw? $(OBJ) lib*
