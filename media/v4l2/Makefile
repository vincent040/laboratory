CC = arm-none-linux-gnueabi-gcc

CPPFLAGS += -I./inc
CPPFLAGS += -I./inc/jpeg
CPPFLAGS += -std=gnu99
CPPFLAGS += -lpthread

LDFLAGS += -L./lib
LDFLAGS += -ljpeg

LDFLAGS += -Wl,-rpath=.

TARGET += show_caminfo 
TARGET += v4l2_yuv
TARGET += snap_yuv 
TARGET += v4l2_jpeg
TARGET += snap_jpeg

all:$(TARGET)

$(TARGET):%:%.c caminfo.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

disclean:clean
	-@$(RM) *.bmp *.jpg 

clean:
	$(RM) $(TARGET)
