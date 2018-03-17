#include "PointLight.h"
#include "errors.h"
namespace GameEngine
{
	unsigned int PointLight::m_pointLights = 0;
	unsigned int PointLight::maxPointLights = 5;
	
	PointLight::PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, glm::vec3 clq) :Light(amb, dif, spe),m_position(pos), m_clq(clq), m_index(m_pointLights++)
	{
		if(m_pointLights > maxPointLights)
			fatalError("To many point lights");

	}

	void PointLight::draw(Shader& shader){
		loadLight(shader);
		m_model->draw(shader);
	}

	PointLight::PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, glm::vec3 clq, Model* model) :Light(amb, dif, spe, model),m_position(pos), m_clq(clq), m_index(m_pointLights++)
	{
		if(m_pointLights > maxPointLights)
			fatalError("To many point lights");

	}
	void PointLight::loadLight(Shader& shader)
	{
		shader.setVec3("pointLights[" + std::to_string(m_index) +  "].position", m_position);
		shader.setVec3("pointLights[" + std::to_string(m_index) +  "].ambient", m_ambient);
		shader.setVec3("pointLights[" + std::to_string(m_index) +  "].diffuse", m_diffuse);
		shader.setVec3("pointLights[" + std::to_string(m_index) +  "].specular", m_specular);
		shader.setFloat("pointLights[" + std::to_string(m_index) +  "].constant", m_clq.x);
		shader.setFloat("pointLights[" + std::to_string(m_index) +  "].linear", m_clq.y);
		shader.setFloat("pointLights[" + std::to_string(m_index) +  "].quadratic", m_clq.z);
		m_updated = true;

	}



}
