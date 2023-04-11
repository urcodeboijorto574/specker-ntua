CC=gcc
CFLAGS=-Wall

specker: specker.cpp
	g++ -o specker specker.cpp

clean:
	rm specker specker.exe
