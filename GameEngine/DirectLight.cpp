#include "DirectLight.h"

namespace GameEngine{


	DirectLight::DirectLight(glm::vec3 direction, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe): Light(amb, dif, spe), m_direction(direction){



	}

	void DirectLight::loadLight(Shader& shader){
		shader.setVec3("dirLight.direction", m_direction.x, m_direction.y, m_direction.z);
		shader.setVec3("dirLight.ambient", m_ambient.x, m_ambient.y, m_ambient.z);
		shader.setVec3("dirLight.diffuse", m_diffuse.x, m_diffuse.y, m_diffuse.z);
		shader.setVec3("dirLight.specular", m_specular.x, m_specular.y, m_specular.z);
	}
			









}
