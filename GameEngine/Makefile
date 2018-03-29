# GameEngine + Game makefile
# Author: Adrian Setniewski (https://github.com/adrset)
# Date: 10-08-2017

CC=g++ -std=c++1z -c -o
CFLAGS=-Wall -O2
CFLAGS_RELEASE=-Wall -O2
LIBS=

# Converts all objects into one GameEnigne lib
GameEngine.a: errors.o InputManager.o Shader.o Window.o Quad.o Renderable.o QuadField.o
	ar rcs $@ $^
	mv GameEngine.a ../build

Renderable.o: Renderable.cpp Renderable.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

QuadField.o: QuadField.cpp QuadField.h
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
