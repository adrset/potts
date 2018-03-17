#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/Entity.h>
#include <GameEngine/Camera.h>
#include <GameEngine/Window.h>
#include <GameEngine/Shader.h>
#include <GameEngine/PointLight.h>
#include <GameEngine/DirectLight.h>
#include <GameEngine/SpotLight.h>

class Game
{
public:
	Game(int width, int height, std::string title);
	~Game();
	void cleanUp();
	void start();
private:
	void processInput();
	int m_width;
	int m_height;
	std::string m_title;
	GameEngine::Camera m_camera;
	GameEngine::SpotLight* m_spotLight;
	GameEngine::DirectLight* m_directLight;
	std::vector<GameEngine::PointLight*> m_pointLights;
	GameEngine::Window* m_window;
	float lastX;
	float lastY;
	void loop();
};

