GCC = gcc
BIN = gps_reader

all: 
	g++ *.cpp -lSDLmain -lSDL -lGLU -lGL

Buoy: Buoy.cpp
	g++ -Wall -o Buoy Buoy.cpp


Sailboat: Sailboat.cpp
	g++ -Wall -o Sailboat Sailboat.cpp

clean: 
	rm -f *~
