#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include "Model.h"
#include "Shader.h"

/*
Author: Adrian Setniewski
Pure virtual Light class, containing basic parameters like colours.


*/

namespace GameEngine{

	class Light{
		public:
			Light(glm::vec3 a, glm::vec3 d, glm::vec3 s);
			Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, Model* model);
			virtual void draw(Shader& shader);
			virtual void loadLight(Shader& shader) = 0;
			glm::vec3 getAmbient() const { return this->m_ambient; }
			glm::vec3 getDiffuse() const { return this->m_diffuse; }
			glm::vec3 getSpecular() const { return this->m_specular; }
			void setAmbient(glm::vec3 amb) { this->m_ambient = amb; }
			void setDiffuse(glm::vec3 dif){ this->m_diffuse = dif; }
			void setSpecular(glm::vec3 spe) { this->m_specular = spe; }
			
		protected:
			
			bool m_updated = false;
			glm::vec3 m_ambient;
			glm::vec3 m_diffuse;
			glm::vec3 m_specular;
			bool m_isEnabled = false;
			Model* m_model;
	};










}

#endif
