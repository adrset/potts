# GameEngine + Game makefile
# Author: Adrian Setniewski (https://github.com/adrset)
# Date: 10-08-2017

CC=g++ -std=c++1z -c -o
CFLAGS=-Wall -O2
CFLAGS_RELEASE=-Wall -O2
LIBS=

# Converts all objects into one GameEnigne lib
GameEngine.a: Camera.o Entity.o errors.o InputManager.o Mesh.o Model.o Shader.o ShaderProgram.o stb_image.o Texture.o Window.o SpotLight.o DirectLight.o PointLight.o Light.o
	ar rcs $@ $^
	mv GameEngine.a ../build

Renderable.o: Renderable.cpp Renderable.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

DirectLight.o: DirectLight.cpp DirectLight.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

SpotLight.o: SpotLight.cpp SpotLight.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

PointLight.o: PointLight.cpp PointLight.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Light.o: Light.cpp Light.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Camera.o: Camera.cpp Camera.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Entity.o: Entity.cpp Entity.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

errors.o: errors.cpp errors.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

InputManager.o: InputManager.cpp InputManager.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Mesh.o: Mesh.cpp Mesh.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Model.o: Model.cpp Model.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Shader.o: Shader.cpp Shader.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

ShaderProgram.o: ShaderProgram.cpp ShaderProgram.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

stb_image.o: stb_image.cpp stb_image.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Texture.o: Texture.cpp Texture.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

Window.o: Window.cpp Window.h
	$(CC) $@ $< $(LIBS) $(CFLAGS)

# Cleanup 

clean:
				rm -f *.o
				rm -f *.a
				rm -f *.gch
	

