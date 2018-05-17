#
# Makefile for Linux application test example.
#
#---------------------------------------------------------------
# Linux application Makefile sample
# make          -- the optical output without debug info
# make clean    -- clean the object file(s)
# make install  -- install the execute file(s) to INSTALLDIR
#---------------------------------------------------------------
# History£º
#			

INSTALLDIR	= /home/zr/nfs/driver/test/

#---------------------------------	/* execute file(s) */
TESTFILE 	= buz_test
#---------------------------------	/* object file(s) */
SRCFILE		= buz_test.c
#---------------------------------	/* header file(s) */
TESTFILE_H	=

CROSS = arm-none-linux-gnueabi-
CC = $(CROSS)gcc
AS = $(CROSS)as
LD = $(CROSS)ld

CFLAGS  += -O2 -Wall

all:   $(TESTFILE)

$(TESTFILE):  $(SRCFILE) $(TESTFILE_H) Makefile 
	$(CC) $(CFLAGS) -o $@ $@.c

clean:
	rm -f $(TESTFILE)
	
install: $(TESTFILE)
	mkdir -p $(INSTALLDIR)
	cp --target-dir=$(INSTALLDIR) $(TESTFILE)


