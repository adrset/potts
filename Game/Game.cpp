#include "Game.h"
#include <GameEngine/Texture.h>
#include <GameEngine/Quad.h>
#include <GameEngine/stb_image.h>
#include <GameEngine/QuadField.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

 // new int c++11 - uniform initialization var{ a}
Game::Game(int width, int height, std::string title): m_width{width}, m_height(height), m_title(title)
{
	m_window = new GameEngine::Window(m_width, m_height, m_title);
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

	std::vector<GameEngine::Quad*> quads;
	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> col;
	for(int i=0;i< 20; i++){
		for(int j=0;j< 20; j++){
			pos.push_back(glm::vec3(20*i, 20*j, 0));
			col.push_back(glm::vec3(i*0.04, j*0.03, (i+j) * 0.024));
			//quads.push_back(new GameEngine::Quad(vertices, indices, sizeof(vertices), sizeof(indices), glm::vec2(20*i, 20*j), glm::vec3(i*0.04, j*0.03, (i+j) * 0.024), 20.0f));
		}
	}

	GameEngine::QuadField field(vertices, indices, sizeof(vertices), sizeof(indices), pos, col, 20.0f);

	//GameEngine::Quad* quad = new GameEngine::Quad(vertices, indices, sizeof(vertices), sizeof(indices), glm::vec2(100), glm::vec3(0.4, 0.1, 0.7), 100.0f);


	// -----------
	while (!m_window->shouldClose())
	{
		processInput();

		// render
		// ------
		m_window->clear();
        lightingShader.setMat4("orthoMatrix", projection);
		field.update(lightingShader);
		/*for(auto* it: quads){
			it->draw(lightingShader);
		}*/

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(m_window->getWindowID());
		glfwPollEvents();
	}

	cleanUp();

}

void Game::processInput()
{
	if(m_window->m_input.isKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(m_window->getWindowID(), true);
}


void Game::cleanUp() {
	m_window->closeWindow();
}


Game::~Game()
{
	std::cout << "Closing game." << std::endl;
}
