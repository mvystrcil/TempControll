#include "timerlib.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"

#include <chrono>

TimerLib::TimerLib(TimeoutCallback callback, int timeout) : m_call(std::move(callback)), m_timeout(timeout)
{
  m_stop = false;
}

bool TimerLib::stopExecution()
{
  m_stop = true;
  return true;
}

bool TimerLib::start()
{
  // make a connection between this object and new thread
  Callback timer = std::bind(&TimerLib::execute, this);
  Supervision::enqueueNewThread(timer);
}


void TimerLib::execute()
{
  dbg << "Execute timer steps";
  
  while(! m_stop)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timeout * 100));
    m_call();
  }
}
