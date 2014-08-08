CC=g++
CFLAGS=-c -Wall

all: dip

dip: main.o arg.o Image.o ImageIO.o Kernel.o RGB.o SeamCarving.o ImageHandler.o
	$(CC) main.o arg.o Image.o ImageIO.o Kernel.o RGB.o SeamCarving.o ImageHandler.o -o tp2

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

arg.o: arg.cpp
	$(CC) $(CFLAGS) arg.cpp

Image.o: Image.cpp
	$(CC) $(CFLAGS) Image.cpp

Kernel.o: Kernel.cpp
	$(CC) $(CFLAGS) Kernel.cpp

RGB.o: RGB.cpp
	$(CC) $(CFLAGS) RGB.cpp

ImageIO.o: ImageIO.cpp
	$(CC) $(CFLAGS) ImageIO.cpp

ImageHandler.o: ImageHandler.cpp
	$(CC) $(CFLAGS) ImageHandler.cpp

SeamCarving.o: SeamCarving.cpp
	$(CC) $(CFLAGS) SeamCarving.cpp

clean:
	rm -rf *o dip
