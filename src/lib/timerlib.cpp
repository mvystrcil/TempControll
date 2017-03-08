#include "timerlib.h"
#include "../lib/logger.h"

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
  m_execution = std::thread(&TimerLib::execute, this);
  m_execution.detach();
}


void TimerLib::execute()
{
  dbg << "Execute timer steps";
  
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  m_call();
  
  /*while(! m_stop)
  {
    
  }*/
}
