#ifndef QUAD_H_
#define QUAD_H_

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Renderable.h"

namespace GameEngine{
  class Quad : public Renderable{
  public:
    Quad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize, glm::vec2 position, float scale);
    glm::vec2 getPosition() const { return m_position; }
    float getScale() const { return m_scale; }
    void setPosition(glm::vec2& position);
    void setScale(float scale);
    void draw(Shader& shader);
    unsigned int getEBO() const { return EBO; }
    unsigned int getVBO() const { return VBO; } // only positions stored
    unsigned int getVAO() const { return VAO; }
  private:
    glm::mat4 m_model; //Reusable mat4
    unsigned int VBO, VAO, EBO;
    glm::vec2 m_position;
    float m_scale;
  };



}

#endif
