#ifndef DIRECTLIGHT_H_
#define DIRECTLIGHT_H_

#include <glm/vec3.hpp>
#include "Shader.h"
#include "Light.h"

namespace GameEngine
{

	class DirectLight : public Light
	{

		public:

			DirectLight(glm::vec3 direction, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe);

			glm::vec3 getDirection() const { return this->m_direction; }
			glm::vec3 getAmbient() const { return this->m_ambient; }
			glm::vec3 getDiffuse() const { return this->m_diffuse; }
			glm::vec3 getSpecular() const { return this->m_specular; }

			void loadLight(Shader& shader);
			
			void setDirection(glm::vec3 dir) { this->m_direction = dir; }
			void setAmbient(glm::vec3 amb) { this->m_ambient = amb; }
			void setDiffuse(glm::vec3 dif){ this->m_diffuse = dif; }
			void setSpecular(glm::vec3 spe) { this->m_specular = spe; }
		private:
			bool m_updated = false;
			glm::vec3 m_direction;
			glm::vec3 m_ambient;
			glm::vec3 m_diffuse;
			glm::vec3 m_specular;
















	};



}


#endif
