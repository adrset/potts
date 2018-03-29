#pragma once
#include <iostream>
#include <Potts/Potts.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/Window.h>
#include <GameEngine/Shader.h>
#include <GameEngine/Timer.h>
class Game
{
public:
	Game(int width, int height, std::string title, float t, float cf, int n, int size);
	~Game();
	void cleanUp();
	void start();
private:
	float m_temp;
	float m_cFactor;
	int m_n;
	int m_size;
	void processInput();
	int m_width;
	int m_height;
	std::string m_title;
	GameEngine::Window* m_window;
	GameEngine::Timer* m_timer;
	float lastX;
	float lastY;
	void loop();
};
