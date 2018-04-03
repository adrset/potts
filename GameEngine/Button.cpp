#include "Button.h"
namespace GameEngine{
  Button::Button(int x, int y, int w, int h, int rounds, std::function<void()> click /* has default param*/) :
  m_x(x), m_y(y), m_w(w), m_h(h), m_rounds(rounds), click(click){

  }

  void Button::setColors(NVGcolor a, NVGcolor b){
    this->m_colorA = a;
    this->m_colorB = b;
  }

  void defaultClick(){
    printf("Halo");
  }

  bool Button::isMouseOver(int x, int y){
    if(x > m_x && x < m_x + m_w && y > m_y && y < m_y + m_h )
      return true;
    else
      return false;
  }

  void Button::draw(NVGcontext* context){
    NVGpaint bg = nvgLinearGradient(context, 0,0,m_w,m_h, m_colorA, m_colorB);
		nvgFillPaint(context, bg);
		nvgRoundedRect(context, m_x,m_y, m_w,m_h, m_rounds);
		nvgFill(context);
  }



}
