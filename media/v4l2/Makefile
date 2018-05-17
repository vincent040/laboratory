CC = arm-none-linux-gnueabi-gcc

CPPFLAGS += -I jpeg-9.0/include
CPPFLAGS += -I sdl-1.2/include/SDL

LDFLAGS += -L jpeg-9.0/lib
LDFLAGS += -L sdl-1.2/lib

LDFLAGS += -Wl,-rpath=./lib

all:v4l2_jpeg.c v4l2_yuv

v4l2_jpeg:v4l2_jpeg.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -ljpeg

v4l2_yuv:v4l2_yuv.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -lSDL


clean:
	$(RM) v4l2_jpeg v4l2_yuv
