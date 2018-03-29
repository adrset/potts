#include "Game.h"

#include <GameEngine/QuadField.h>
#include <vector>
#include <cstdlib>
#include <fstream>

#include <iostream>
#include <unistd.h>
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

 // new int c++11 - uniform initialization var{ a}
Game::Game(int width, int height, std::string title, float t, float cf, int n, int size,int fps): m_temp(t), m_cFactor(cf), m_n(n), m_size(size), m_width{width}, m_height(height), m_title(title)
{
	m_window = new GameEngine::Window(m_width, m_height, m_title);
	m_timer = new GameEngine::Timer(fps);
	lastX = m_width / 2.0f;
	lastY = m_height / 2.0f;
	//glm::vec3 pos, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, glm::vec3 clq
		// spotLight
	//loop will be probably public soon
}

void Game::start(){
	loop();
}

void Game::loop() {

	srand(time(NULL));
	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	GameEngine::Shader lightingShader("2dshader.vs", "2dshader.fs");

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
  	lightingShader.use();

	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)m_width, (GLfloat)m_height, 0.0f, -10.0f, 10.00f);
	lightingShader.setMat4("orthoMatrix", projection);

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
 
	GameEngine::QuadField field(vertices, indices, sizeof(vertices), sizeof(indices), pos, col, ((float)m_width) / ((float)m_size));

	//GameEngine::Quad* quad = new GameEngine::Quad(vertices, indices, sizeof(vertices), sizeof(indices), glm::vec2(100), glm::vec3(0.4, 0.1, 0.7), 100.0f);


	int fps=60;
	// -----------

	while (!m_window->shouldClose())
	{
		m_timer->start();

		processInput();

		// render
		// ------
		m_window->clear();
        lightingShader.setMat4("orthoMatrix", projection);
		field.update(lightingShader);

		//POTTS INTENSIFIES!!
		for(int i=0;i<m_size * m_size;i++){
        	m_potts->MetropolisStep();
		}

        for(int i=0;i< m_size; i++){
            for(int j=0;j< m_size; j++){
                float color = 0.333 * m_potts->getSpin(i,j);
                field.setColor(i*m_size+j, glm::vec3(0,color/2,color));
            }
        }
        //POTTS DEMINISHED :(

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(m_window->getWindowID());
		glfwPollEvents();
		fps = 1.0/m_timer->end();
		
		if(iter == 400){ // hardcoded :s
			iter = 0;
			std::cout << "FPS: " << fps << std::endl << "T: " << m_potts->getTemperature() << std::endl;;

		}else{
			iter++;
		}

		m_timer->wait();

		
	}

	cleanUp();

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
	std::cout << "Closing game." << std::endl;
}
