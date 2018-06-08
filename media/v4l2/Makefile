CC = arm-none-linux-gnueabi-gcc

JPEGPATH=
SDLPATH =

CPPFLAGS += -I $(JPEGPATH)/include
LDFLAGS += -L $(JPEGPATH)/lib

LDFLAGS += -Wl,-rpath=.

all:v4l2_jpeg v4l2_yuv

v4l2_jpeg:v4l2_jpeg.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -ljpeg

v4l2_yuv:v4l2_yuv.c caminfo.c
	$(CC) $^ -o $@ -std=gnu99


clean:
	$(RM) v4l2_jpeg v4l2_yuv
