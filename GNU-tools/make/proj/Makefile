vpath %.h inlcude
vpath %.c src

LIBPATH = lib
SRCPATH = src

CFLAGS = -Wall -Wl,-rpath=$(LIBPATH)
SO_FLAGS = -shared -fPIC
AR_FLAGS = rcs

SRC = $(filter-out $(SRCPATH)/main.c, $(wildcard $(SRCPATH)/*.c))
OBJ = $(patsubst %.c, %.o, $(SRC))

main:main.c
	$(CC) $^ -o $@ $(CFLAGS) -L$(LIBPATH) -lsum

install:
	$(MAKE) -C src
ifdef SO_FLAGS
	$(CC) $(SO_FLAGS) -o $(LIBPATH)/libsum.so $(OBJ)
else
	$(AR) $(AR_FLAGS) -o $(LIBPATH)/libsum.a $(OBJ)
endif

clean:
	-@$(RM) main $(SRCPATH)/*.o $(LIBPATH)/lib*
