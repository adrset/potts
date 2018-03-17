#include "Entity.h"

namespace GameEngine
{


	void Entity::draw(Shader& shader)
	{
		m_model = glm::translate(m_model, m_position);

		// hardcoded for testing purposes
		m_model = glm::scale(m_model, glm::vec3(0.05f));
		m_model = glm::translate(m_model, glm::vec3(0.0f, -5.0f, 0.0f));
		

		// end
		m_model = glm::rotate(m_model, glm::radians(m_eulerAngles.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_model = glm::rotate(m_model, glm::radians(m_eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_model = glm::rotate(m_model, glm::radians(m_eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
		
		shader.setMat4("model", m_model);
		
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].draw(shader);
			
		}
	}

	void Entity::incPos(glm::vec3 pos)
	{
		this->m_position += pos;	

	}
	void Entity::incAngles(glm::vec3 angles)
	{
		this->m_eulerAngles += angles;	

	}

	void Entity::setPos(glm::vec3 pos)
	{
		this->m_position = pos;

	}
	void Entity::setAngles(glm::vec3 angles)
	{
		this->m_eulerAngles = angles;
	
	}

	Entity::Entity(const char *path) : Model(path)
	{


	}

	Entity::~Entity()
	{


	}



}
