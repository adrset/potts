#include "Light.h"

namespace GameEngine{


	void Light::draw(Shader& shader){

	}

	Light::	Light(glm::vec3 a, glm::vec3 d, glm::vec3 s) : m_ambient(a), m_diffuse(d), m_specular(s){

	}

	Light::	Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, Model* model) : m_ambient(a), m_diffuse(d), m_specular(s), m_model(model){

	}











}
