#include "SpotLight.h"

namespace GameEngine{
		SpotLight::SpotLight(glm::vec3& pos, glm::vec3& dir, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, glm::vec3 clq, glm::vec2 cut) :
		 Light(amb, dif, spe),
		 m_direction(dir),
		 m_position(pos),
		 m_clq(clq),
		 m_cutOff(cut) {

		}


		void SpotLight::loadLight(Shader& shader){
			shader.setVec3("spotLight.direction", m_direction);
			shader.setVec3("spotLight.position", m_position);
			shader.setVec3("spotLight.ambient", m_ambient);
			shader.setVec3("spotLight.diffuse", m_diffuse);
			shader.setVec3("spotLight.specular", m_specular);
			shader.setFloat("spotLight.constant", m_clq.x);
			shader.setFloat("spotLight.linear", m_clq.y);
			shader.setFloat("spotLight.quadratic", m_clq.z);
			shader.setFloat("spotLight.cutOff", m_cutOff.x);
			shader.setFloat("spotLight.outerCutOff", m_cutOff.y);

		}



















}
