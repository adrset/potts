#include "Timer.h"

namespace GameEngine{

Timer::Timer(unsigned int fps) : m_desiredFPS(fps){

}

void Timer::start(){
   m_lastFrameTime = std::chrono::system_clock::now();
}

double Timer::end(){
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsedSeconds = end-m_lastFrameTime;
  m_lastFrameDuration = elapsedSeconds.count();
  return elapsedSeconds.count();
}


}
