#include "Game.h"

#include <vector>
#include <cstdlib>
#include <fstream>

#include <iostream>
#include <unistd.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg_gl.h>

 // new int c++11 - uniform initialization var{ a}
Game::Game(int width, int height, std::string title, float t, float cf, int n, int size,int fps): m_temp(t), m_cFactor(cf), m_n(n), m_size(size), m_width{width}, m_height(height), m_title(title)
{
	GameEngine::Window::init();

	m_window = new GameEngine::Window(m_width, m_height, m_title);

	m_window2 = new GameEngine::Window(m_width, m_height, "m_title", m_window->getWindowID());



		// NanoVG init
	m_window2->makeContextCurrent();
	m_vg = nvgCreateGL3( NVG_STENCIL_STROKES | NVG_DEBUG);
	if (m_vg == NULL) {
		printf("Could not init nanovg.\n");
	}
	m_window->makeContextCurrent();

	m_timer = new GameEngine::Timer(fps);
	lastX = m_width / 2.0f;
	lastY = m_height / 2.0f;

	srand(time(NULL));

	// build and compile our shader zprogram
	// ------------------------------------
	m_shader = new GameEngine::Shader("2dshader.vs", "2dshader.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
       1.0f,  1.0f, 0.0f,  // top right
       1.0f, -1.0f, 0.0f,  // bottom right
      -1.0f, -1.0f, 0.0f,  // bottom left
      -1.0,  1.0f, 0.0f   // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,  // first Triangle
      1, 2, 3   // second Triangle
  };

  srand(time(NULL));
  m_shader->use();

	m_projection = glm::ortho(0.0f, (GLfloat)m_width, (GLfloat)m_height, 0.0f, -10.0f, 10.00f);
	m_shader->setMat4("orthoMatrix", m_projection);

	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> col;


   /* float temperature       = 0.001;
    float couplingFactor    = 1;
    float nSpins            = 2;*/
  m_potts = new Potts::MainMatrix(m_size, m_temp, m_cFactor, m_n, 0 );    //MainMatrix(int newMatrixSize, float simTemperature, float couplingFactor, int maxSpin, int minSpin );

  int offset = m_width / m_size;

	for(int i=0;i< m_size; i++){
		for(int j=0;j< m_size; j++){
            float color = 0.3 * (float)m_potts->getSpin(i,j);
			pos.push_back(glm::vec3(offset*i, offset*j, 0));
			col.push_back(glm::vec3(color, 0.2, 0.2));
		}
	}

    /*
        dobre wybory:
        t=3     j=1     max=3   min=0
        t=      j=      max=    min=
        t=      j=      max=    min=
        t=      j=      max=    min=
    */
	m_field = new GameEngine::QuadField(vertices, indices, sizeof(vertices), sizeof(indices), pos, col, ((float)m_width) / ((float)m_size));
	//m_window2->makeContextCurrent();

	//m_graphWindow = new GameEngine::Window(m_width, m_height, "sec", m_window->getWindowID());
	m_window2->changePosition(m_window2->getWindowPosition().width+5, 0);



}

void Game::start(){
	loop();
}

void Game::loop() {
	NVGpaint bg;
	while (!m_window->shouldClose() && !m_window2->shouldClose())
	{
		m_timer->start();
		processInput();
		m_window->makeContextCurrent();

		m_window->clear();

    m_shader->setMat4("orthoMatrix", m_projection);

		m_field->update(m_shader);

  	gameLogic();

		// GUI drawing
		m_window2->makeContextCurrent();
		m_window2->clear();

		nvgBeginFrame(m_vg, m_window2->getInfo().width, m_window2->getInfo().height, m_window2->getFramebufferPixelRatio());

		nvgBeginPath(m_vg);
		bg = nvgLinearGradient(m_vg, 0,0,0,800, nvgRGBA(12,12,255,16), nvgRGBA(0,0,0,16));
		nvgFillPaint(m_vg, bg);
		nvgRect(m_vg, 0,0, 800,800);
		nvgFill(m_vg);

		nvgEndFrame(m_vg);

		m_window->swapBuffers();
		m_window2->swapBuffers();

		glfwPollEvents();

		waitAndShoutFPS();


	}

	cleanUp();

}

void Game::waitAndShoutFPS(){
		int fps = 1.0/m_timer->end();

		std::cout << "FPS: " << fps << std::endl << "T: " << m_potts->getTemperature() << std::endl;;

		m_timer->wait();

}

void Game::gameLogic(){
	//POTTS INTENSIFIES!!
		for(int i=0;i<m_size * m_size;i++){
        	m_potts->MetropolisStep();
		}

        for(int i=0;i< m_size; i++){
            for(int j=0;j< m_size; j++){
                float color = 0.333 * m_potts->getSpin(i,j);
                m_field->setColor(i*m_size+j, glm::vec3(0,color/2,color));
            }
        }
}

void Game::processInput()
{
	if(m_window->m_input.isKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(m_window->getWindowID(), true);
	if(m_window->m_input.isKeyPressed(GLFW_KEY_1))
		m_potts->adjustTemperature(0.01f);
	if(m_window->m_input.isKeyPressed(GLFW_KEY_2))
		m_potts->adjustTemperature(-0.01f);
}


void Game::cleanUp() {
	m_window->closeWindow();
}


Game::~Game()
{
	delete m_window;
//	delete m_window2;
	delete m_timer;
	std::cout << "Closing game." << std::endl;
}
