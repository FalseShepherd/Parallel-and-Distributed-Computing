//
//  Timer.cpp
//
#include "Timer.h"

Timer::Timer() {
  RestartTimer();
}


void Timer::RestartTimer() {
  startTime = std::chrono::high_resolution_clock::now();
}


double Timer::GetElapsedTime() {
  auto curTime =  std::chrono::high_resolution_clock::now();
  auto difference = curTime - startTime;
  std::chrono::duration<double> time_span = 
    std::chrono::duration_cast<std::chrono::duration<double>>(difference);
  return time_span.count();
}
