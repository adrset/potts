# GameEngine + Game makefile
# Author: Adrian Setniewski (https://github.com/adrset)
# Date: 10-08-2017

CC=g++ -std=c++1z -c -o
CFLAGS=-Wall -O3 -I../include/
CFLAGS_RELEASE=-Wall -O2 -I../include/
LIBS=

# Converts all objects into one GameEnigne lib
GameEngine.a: errors.o InputManager.o Shader.o Window.o Quad.o Renderable.o QuadField.o Timer.o glad.o nanovg.o
	ar rcs $@ $^
	mv GameEngine.a ../build

Renderable.o: Renderable.cpp Renderable.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

glad.o: glad.c
			$(CC) -c $< -o $@ $(INC) $(CFLAGS)

nanovg.o: nanovg.c
				$(CC) -c $< -o $@ $(INC) $(CFLAGS)

QuadField.o: QuadField.cpp QuadField.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Timer.o: Timer.cpp Timer.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Quad.o: Quad.cpp Quad.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

errors.o: errors.cpp errors.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

InputManager.o: InputManager.cpp InputManager.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Shader.o: Shader.cpp Shader.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Window.o: Window.cpp Window.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

# Cleanup

clean:
				rm -f *.o
				rm -f *.a
				rm -f *.gch
