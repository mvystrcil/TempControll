#ifndef TIMERLIB_H
#define TIMERLIB_H

#include <functional>
#include <thread>
#include <vector>

typedef std::function<void (void)> TimeoutCallback;

class TimerLib
{
private:
  class Event {
    public:
      Event(TimeoutCallback callback, int timeout);
      TimeoutCallback m_callback;
      int m_timeout;
      bool m_stop;
      
      void timeout();
  };
  
  std::vector<Event> threads;
  
public:
  TimerLib();
  
  const int PROBLEM_WHILE_THREAD_CREATION = -1;

    // https://thebytekitchen.com/2013/01/14/harder-to-c-aligned-memory-allocation-4/
    int registerHandler(TimeoutCallback callback, int timeout);
    bool stopExecution();
    
    
    //void addHandler(std::function<void(void)> callback);
    //void addHandler(std::function<void(void)> callback);
    //bool registerHandler(std::function<void(int)> callback);
};

#endif // TIMERLIB_H
