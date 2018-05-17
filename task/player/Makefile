CPPFLAGS += -I./sdl-1.2/include/SDL
CPPFLAGS += -I./madplay/include

LDFLAGS += -L./sdl-1.2/lib
LDFLAGS += -L./madplay/lib
LDFLAGS += -lpthread

all: player_thread player_proc


player_thread:player_thread.c
	arm-none-linux-gnueabi-gcc $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

player_proc:player_proc.c
	arm-none-linux-gnueabi-gcc $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	-@rm *.o .*.sw? player_ts
