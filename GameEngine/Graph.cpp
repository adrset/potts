#include "Graph.h"
namespace GameEngine{
  Graph::Graph() : m_updates(0){

      m_points = new float[MAX_POINTS * 2];
      m_lastUpdated = 1;
      glGenVertexArrays(1, &m_vao);
      glGenBuffers(1, &m_vbo);

      glBindVertexArray(m_vao);

      glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
      glBufferData(GL_ARRAY_BUFFER, MAX_POINTS * 2 * 4, m_points, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glBindVertexArray(0);



  }

  void Graph::addPoint(float x, float y){
    if(iter / 2 == MAX_POINTS ){
      iter = 0;
    }

    if(x>maxX)  maxX = x;
    if(y>maxY)  maxY = y;

  //  size_t pos = m_points->size() - 1;
  //  m_points[iter++ % MAX_POINTS] = Point(x, y);
    m_points[iter++] = x;
    m_points[iter++] = y;

  }

  void Graph::draw(Shader* shader){
      glBindVertexArray(m_vao);
glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
      glBufferSubData(GL_ARRAY_BUFFER,0, MAX_POINTS * 2 * 4, m_points);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

      shader->use();
      shader->setFloat("maxX", maxX);
      shader->setFloat("maxY", maxY);
      // bad

      glDrawArrays(GL_LINE_STRIP, 0, iter / 2);
      glBindVertexArray(0);

  }
}
