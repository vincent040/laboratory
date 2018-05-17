SRC = $(wildcard *.c)
OBJ = $(filter-out main.o, $(patsubst %.c, %.o, $(SRC)))

all:$(OBJ)

$(OBJ):%.o:%.c
	$(CC) -c -o $@ $<

clean:
	$(RM) *.o -f
