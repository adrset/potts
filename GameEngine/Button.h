#ifndef BUTTON_H_
#define BUTTON_H_
#include <nanovg/nanovg.h>
#include <functional>
#include "Renderable.h"
namespace GameEngine{
  void defaultClick();
  
  class Button{
  public:
    Button(int x, int y, int w, int h, int rounds = 0, std::function<void()> click = defaultClick);
    void draw(NVGcontext* context);
    void setColors(NVGcolor a, NVGcolor b);
    bool isMouseOver(int x, int y);
    std::function<void()> click;
  private:
    int m_x, m_y, m_w, m_h, m_rounds;
    NVGcolor m_colorA;
    NVGcolor m_colorB;



  };



}
#endif
