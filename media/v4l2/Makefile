
CC = arm-none-linux-gnueabi-gcc

#########################
CPPFLAGS += -I./inc
CPPFLAGS += -I./inc/jpeg
CPPFLAGS += -std=gnu99
CPPFLAGS += -lpthread
#########################
LDFLAGS += -L./lib
LDFLAGS += -ljpeg
LDFLAGS += -Wl,-rpath=.
#########################
TARGET += caminfo_test
TARGET += videostream_yuv
TARGET += videostream_jpg
TARGET += snap_yuv2bmp
TARGET += snap_yuv2jpg
#########################
all:$(TARGET)

$(TARGET):%:%.c caminfo.c
	$(CC) $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

disclean:clean
	-@$(RM) *.bmp *.jpg 

clean:
	$(RM) $(TARGET)
