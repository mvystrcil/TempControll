#ifndef TIMERLIB_H
#define TIMERLIB_H

#include <functional>
#include <thread>

typedef std::function<void (void)> TimeoutCallback;

class TimerLib
{
private:
  TimeoutCallback m_callback;
  bool m_stop;
  std::thread m_execution;
  std::chrono::milliseconds m_timeout;
  
  void timeout();
  
public:
  TimerLib();

    // https://thebytekitchen.com/2013/01/14/harder-to-c-aligned-memory-allocation-4/
    bool registerHandler(TimeoutCallback callback, int timeout);
    bool stopExecution();
    
    
    //void addHandler(std::function<void(void)> callback);
    //void addHandler(std::function<void(void)> callback);
    //bool registerHandler(std::function<void(int)> callback);
};

#endif // TIMERLIB_H
