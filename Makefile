GCC = gcc
BIN = gps_reader

all: 
	g++ *.cpp -lSDLmain -lSDL -lGLU -lGL

Buoy: Buoy.cpp
	g++ -Wall -o Buoy Buoy.cpp


sailboat: sailboat.cpp
	g++ -Wall -o sailboat sailboat.cpp

clean: 
	rm -f *~
