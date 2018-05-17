##############################
# servfox Makefile
##############################

#INSTALLROOT=$(PWD)
#CROSS_COMPILE = arm-linux-gnu-

DEBUG=1

CC = $(CROSS_COMPILE)gcc

ifdef CROSS_COMPILE
TARGET_FS_PATH = /opt/filesystem
endif

BINARY = mydaemon

BIN_PATH =$(TARGET_FS_PATH)/usr/bin

INSTALL=install

#WARNINGS = -Wall \
#           -Wundef -Wpointer-arith -Wbad-function-cast \
#           -Wcast-align -Wwrite-strings -Wstrict-prototypes \
#           -Wmissing-prototypes -Wmissing-declarations \
#           -Wnested-externs -Winline -Wcast-qual -W \
#           -Wno-unused
#           -Wunused

ifdef DEBUG
 	CFLAGS = -g -O0 -DDEBUG
else
	CFLAGS = -O2
endif

CFLAGS += -DLINUX $(WARNINGS)

#LIBS= -lpthread


OBJ= ${patsubst %.c, %.o, ${wildcard *.c}}
		
all:$(BINARY)
	
clean:
	@echo "Cleaning up directory."
	- rm -f .*.sw? *.a *.o $(BINARY)   core *~ log errlog

$(BINARY):$(OBJ)
	$(CC) $(CFLAGS) -o $(BINARY) $(OBJ) $(LIBS)
	
%.o : %.c	
	$(CC) $(CFLAGS) -c -o $@ $<
	 
install: $(BINARY)
	$(INSTALL) -s -m 755 -g root -o root $(BINARY) $(BIN_PATH) 

dist: clean
	tar czf ../farsight_daemon_demo_with_debug_support_1.1.tar.gz ../daemon
