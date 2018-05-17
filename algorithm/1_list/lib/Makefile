SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

LIB_PATH = /lib
HEADER_PATH = /usr/include

libvlist.a:$(OBJ)
	$(AR) crs $@ $^
	@$(RM) $(OBJ)

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) -o $@ $^ -c

install:
	cp libvlist.a $(LIB_PATH)
	cp head4list.h $(HEADER_PATH)

clean:
	$(RM) .*.sw? $(OBJ) lib*
