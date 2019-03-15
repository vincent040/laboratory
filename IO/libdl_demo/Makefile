main:main.c install 
	gcc main.c  -o main -ldl -Wl,-rpath=.

install:color.o outlook.o
	gcc -shared -fPIC -o libcolor.so color.o
	gcc -shared -fPIC -o liboutlook.so outlook.o

color.o:color.c
	gcc color.c -o color.o -c -fPIC
outlook.o:outlook.c
	gcc outlook.c -o outlook.o -c -fPIC

clean:
	rm main *.o *.so
