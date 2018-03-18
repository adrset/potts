#include "Game.h"
#include <GameEngine/Texture.h>
#include <GameEngine/Quad.h>
#include <GameEngine/stb_image.h>

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

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	GameEngine::Shader lightingShader("2dshader.vs", "2dshader.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
       0.5f,  0.5f, 0.0f,  // top right
       0.5f, -0.5f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f,  // bottom left
      -0.5f,  0.5f, 0.0f   // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,  // first Triangle
      1, 2, 3   // second Triangle
  };

	GameEngine::Quad* quad = new GameEngine::Quad(vertices, indices, sizeof(vertices), sizeof(indices));



	// -----------
	while (!m_window->shouldClose())
	{
		processInput();

		// render
		// ------
		m_window->clear();
		
		quad->draw(lightingShader);

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
