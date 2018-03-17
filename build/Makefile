# GameEngine + Game makefile
# Author: Adrian Setniewski (https://github.com/adrset)
# Date: 10-08-2017
# Prerequisites
#	Operation System: Linux, preferably Debian, Ubuntu based.
#	Compiler: Latest GNU GCC compiler
# 	Libs:
#		glfw3 - Lightweight multiplatform library for OpenGL.
#		glew - OpenGL extension wrangler library.
#		glm - OpenGL mathematics library.
#		assimp - 3D object loader and more.
#
# Explaination: 
# $@ means the target
# $^ means all prerequisites
# $< means only the first prerequisite    

CC=g++ -std=c++17 -c -o
CCO=g++ -std=c++17
CFLAGS=-Wall
CFLAGS_RELEASE=-Wall -O2
LIBS=-lglfw -lm -lGLEW -lGLU -lGL -lassimp
TARGET = game

$(TARGET): final 

final: 
	$(CCO) -o gameBinary main.o Game.o -L. -l:GameEngine.a $(LIBS)

clean:
				rm -f *.o
				rm -f *.a
				rm -f *.gch
	

