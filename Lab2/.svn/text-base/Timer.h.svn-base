//
// Timer - measure elapsed real time using highest available
//         resolution clock. Requires C++11 or later.
//
// Example use:
//    ...
//    Timer tAll;
//    Timer t;
//      [code block1 to be timed]
//    double elapsed1 = t.GetElapsedTime();
//    ...
//    t.RestartTimer();
//      [code block2 to be timed]
//    double elapsed2 = t.GetElapsedTime();
//    ...
//    double totalElapsed = tAll.GetElapsedTime();
//

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
  Timer();
  // Default assignment and copy/move work with this class

  // Restart timing
  void RestartTimer();

  // Get elapsed time in seconds since constructor or RestartTimer called
  double GetElapsedTime();

private:
  std::chrono::high_resolution_clock::time_point startTime;
};

#endif // TIMER_H
