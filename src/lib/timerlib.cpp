#include "timerlib.h"
#include "../lib/logger.h"

#include <chrono>

TimerLib::TimerLib()
{

}

/*void TimerLib::addHandler(std::function<void(void)> callback)
{
	dbg << "Registered callback function " << lf;
	dbg << "Call this func immediatelly" << lf;
	callback();
}*/

bool TimerLib::registerHandler(TimeoutCallback callback, int timeout)
{
  m_callback = callback;
  m_timeout = m_timeout;
  m_stop = false;
  m_execution = std::thread(&TimerLib::timeout, this);
  
  m_execution.join();
  
  dbg << "Register callback to fire every " << timeout;
}

bool TimerLib::stopExecution()
{
  return true;
}

void TimerLib::timeout()
{
  dbg << "Thread started, sleep before emitting signal";
  
  /*while(! m_stop)
  {
    std::this_thread::sleep_for(m_timeout);
    dbg << "Will sleep for some time " << lf;
  }*/
}



