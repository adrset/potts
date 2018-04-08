#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "Renderable.h"

namespace GameEngine{

  typedef struct Point{
    float xPos;
    float yPos;
    Point(float x, float y) : xPos(x),yPos(y){};
    Point(){};
  }Point;
  class Graph : public Renderable{
  public:
    Graph();
    void draw(Shader* shader);
    void addPoint(float x, float y);
  private:
    unsigned int iter = 0;
    float maxX;
    float maxY;
    const unsigned int MAX_POINTS = 10000;
    unsigned int m_updates;
    unsigned int m_vao, m_vbo;
    float* m_points;
    unsigned int m_lastUpdated;

  };

}

#endif
