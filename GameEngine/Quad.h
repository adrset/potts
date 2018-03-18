#ifndef QUAD_H_
#define QUAD_H_

#include "Shader.h"
#include "Renderable.h"

namespace GameEngine{
  class Quad : public Renderable{
  public:
    Quad(float *vertices, unsigned int *indices, size_t vSize, size_t iSize);

    void draw(Shader& shader);
    unsigned int getEBO() const { return EBO; }
    unsigned int getVBO() const { return VBO; } // only positions stored
    unsigned int getVAO() const { return VAO; }
  private:
    unsigned int VBO, VAO, EBO;
  };



}

#endif
