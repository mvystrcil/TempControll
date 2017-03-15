#ifndef TIMERLIB_H
#define TIMERLIB_H

#include <functional>
#include <thread>
#include <vector>

typedef std::function<void (void)> TimeoutCallback;

class TimerLib
{
private:  
  std::thread m_execution;
  int m_timeout;
  bool m_stop;
  void execute();
  void sleep(int milliseconds);
  
public:
  TimerLib(TimeoutCallback callback, int timeout);
  virtual ~TimerLib();
  
  static const int PROBLEM_WHILE_THREAD_CREATION = -1;
  TimeoutCallback m_call;
  
  // https://thebytekitchen.com/2013/01/14/harder-to-c-aligned-memory-allocation-4/
  bool stopExecution();
  bool start();
};

#endif // TIMERLIB_H
