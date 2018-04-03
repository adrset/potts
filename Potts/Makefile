# GameEngine + Game makefile
# Author: Adrian Setniewski (https://github.com/adrset)
# Date: 10-08-2017

CC=g++ -std=c++1z -c -o
CCO=g++ -std=c++17
CFLAGS=-Wall
CFLAGS_RELEASE=-Wall -O3
LIBS=-lglfw -lm -lGLEW -lGLU -lGL -lassimp
INC=-I../
TARGET=game

$(TARGET): Potts.a

Potts.a: Potts.o
	ar rcs $@ $^
	mv Potts.a ../build

Potts.o: Potts.cpp
	$(CC) -c $< -o $@ $(INC) $(CFLAGS_RELEASE)

# Cleanup

clean:
				rm -f *.o
				rm -f *.a
				rm -f *.gch
