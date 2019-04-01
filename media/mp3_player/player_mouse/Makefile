CPPFLAGS += -I/usr/local/sdl1.2/include/SDL
CPPFLAGS += -I/usr/local/audio/include
CPPFLAGS += -I/usr/local/tslib/include

LDFLAGS += -L/usr/local/sdl1.2/lib
LDFLAGS += -L/usr/local/audio/lib
LDFLAGS += -L/usr/local/tslib/lib
LDFLAGS += -lSDL
LDFLAGS += -lmad
LDFLAGS += -lts


player_mouse:player_mouse.c mp3decode.c
	arm-none-linux-gnueabi-gcc $^ -o $@ $(CPPFLAGS) $(LDFLAGS)
