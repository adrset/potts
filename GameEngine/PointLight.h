#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include <glm/vec3.hpp>
#include "Shader.h"
#include "Light.h"
#include "Model.h"
namespace GameEngine
{

	class PointLight : public Light
	{

		public:

			PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, glm::vec3 clq);
			PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, glm::vec3 clq, Model* model);
			glm::vec3 getPosition() const { return this->m_position; }
			
			glm::vec3 getClq() const { return this->m_clq; }

			void loadLight(Shader& shader);
			void draw(Shader& shader);
			
			void setPosition(glm::vec3 pos) { this->m_position = pos; }
			void setClq(glm::vec3 clq) { this->m_clq = clq; }

			static unsigned int maxPointLights;
		private:
			static unsigned int m_pointLights;
			
			glm::vec3 m_position;
			glm::vec3 m_clq; // constant, linear, quadratic
			unsigned int m_index;















	};



}


#endif
