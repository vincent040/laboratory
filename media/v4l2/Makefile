CC = arm-none-linux-gnueabi-gcc

JPEGPATH=

CPPFLAGS += -I $(JPEGPATH)/include
LDFLAGS += -L $(JPEGPATH)/lib

LDFLAGS += -Wl,-rpath=.

all:v4l2_jpeg v4l2_yuv snap_yuv

v4l2_jpeg:v4l2_jpeg.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS) -ljpeg

v4l2_yuv:v4l2_yuv.c caminfo.c
	$(CC) $^ -o $@ -std=gnu99 -lpthread

snap_yuv:snap_yuv.c caminfo.c
	$(CC) $^ -o $@ -std=gnu99 -lpthread


clean:
	$(RM) v4l2_jpeg v4l2_yuv snap_yuv
