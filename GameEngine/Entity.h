
#ifndef ENTITY_H_
#define ENTITY_H_

#include "Shader.h"
#include "Model.h"

namespace GameEngine
{

	class Entity : public Model{
		public:
		void draw(Shader& shader);
		glm::vec3 getPos() const { return m_position; }
		glm::vec3 getAngles() const { return m_eulerAngles; }
		void setPos(glm::vec3 pos);
		void setAngles(glm::vec3 angles);
		void incPos(glm::vec3 pos);
		void incAngles(glm::vec3 angles);
		Entity(const char *path);
		~Entity();
		private:
		glm::mat4 m_model;
		glm::vec3 m_position;
		glm::vec3 m_eulerAngles; // x->pith, y->yaw, z->roll

	};




}

#endif
