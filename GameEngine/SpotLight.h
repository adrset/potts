#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_
#include "Light.h"

namespace GameEngine{



	class SpotLight : public Light{


		public:
			SpotLight(glm::vec3& pos, glm::vec3& dir, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, glm::vec3 clq, glm::vec2 cut);

			glm::vec3 getDirection() const { return this->m_direction; }
			glm::vec3 getPosition() const { return this->m_position; }
			glm::vec3 getClq() const { return this->m_clq; }
			glm::vec2 getCutOff() const { return this->m_cutOff; }

			void loadLight(Shader& shader);

		private:


			glm::vec3& m_direction;
			glm::vec3& m_position;
			glm::vec3 m_clq; // constant, linear, quadratic
			glm::vec2 m_cutOff;








	};

















}

#endif
