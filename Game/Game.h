#pragma once
#include <iostream>
#include <Potts/Potts.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GameEngine/Window.h>
#include <GameEngine/Shader.h>
#include <GameEngine/Timer.h>
#include <GameEngine/QuadField.h>
#include <GameEngine/Button.h>
#include <nanovg/nanovg.h>

class Game
{
public:
	Game(int width, int height, std::string title, float t, float cf, int n, int size, int fps);
	~Game();
	void cleanUp();
	void start();
	void gameLogic(bool * UgottaWORK);
	void waitAndShoutFPS();
private:
	glm::mat4 m_projection;
	GameEngine::Shader* m_shader;
	GameEngine::QuadField* m_field;
	Potts::MainMatrix* m_potts;
	Potts::InfoPack* m_data;
	//Potts::MultiPack* m_multi;
	Potts::MultiPack2* m_multi2;
	int stepsDone;
	float m_temp;
	float m_cFactor;
	int m_n;
	int m_fps = 60;
	int fontNormal;
	int m_size;
	void processInput();
	int m_width;
	int m_height;
	NVGcontext* m_vg = nullptr;
	std::string m_title;
    std::vector<GameEngine::Button> m_buttons;
	GameEngine::Window* m_window2;
	GameEngine::Window* m_window;
	GameEngine::Timer* m_timer;
	float lastX;
	float lastY;
	void loop();
};
