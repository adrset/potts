#ifndef TIMER_H_
#define TIMER_H_
#include <chrono>
#include <ctime>

namespace GameEngine{
class Timer {
public:
  Timer(unsigned int fps);
  void start();
  double end();

private:
  unsigned int m_desiredFPS;
  double m_lastFrameDuration;
  std::chrono::time_point<std::chrono::system_clock> m_lastFrameTime;
};

}














#endif
