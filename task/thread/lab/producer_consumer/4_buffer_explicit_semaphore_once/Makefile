CFLAGS = -O0 -Wall -ggdb -lpthread

buffer_seminit:main.c buffer_seminit.c buffer_initmutex.c
	- $(CC) -o $@ $^ $(CFLAGS)

clean:
	@ - $(RM) .*.sw? *.o buffer_seminit

.PHONY:clean
