LIBPATH = lib/
INCPATH = inc/
SRCPATH = src/

vpath %.so= $(LIBPATH)
vpath %.h = $(INCPATH)
vpath %.c = $(SRCPATH)

CC = arm-none-linux-gnueabi-gcc

# FIXME # 从make外部传参
JPGPATH = 

CPPFLAGS += -I$(INCPATH)
LDFLAGS  += -ldl

CPPFLAGS += -I$(JPGPATH)/include
LDFLAGS  += -L$(JPGPATH)/lib
LDFLAGS  += -ljpeg

showimg:showimg.c
	$(CC) $< -o $@ $(CPPFLAGS) $(LDFLAGS)

# 安装自定义库文件
install:$(LIBPATH)/libbmp.so $(LIBPATH)/libjpg.so

$(LIBPATH)/libbmp.so:bmp.o
	$(CC) $< -o $@ -fPIC -shared
	$(RM) $<
bmp.o:bmp.c
	$(CC) $< -o $@ $(CPPFLAGS) -fPIC -c

$(LIBPATH)/libjpg.so:jpg.o
	$(CC) $< -o $@ -fPIC -shared
	$(RM) $<
jpg.o:jpg.c
	$(CC) $< -o $@ $(CPPFLAGS) -fPIC -c

clean:
	$(RM) *.o .*.sw? core showimg

distclean:clean
	$(RM) $(LIBPATH)/*.so

.PHONY:clean distclean
