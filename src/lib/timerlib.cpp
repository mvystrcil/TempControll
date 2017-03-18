#include "timerlib.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"
#include "../consts/timeouts.h"

#include <chrono>

TimerLib::TimerLib(TimeoutCallback callback, int timeout) : m_call(std::move(callback)), m_timeout(timeout)
{
  m_stop = false;
}

TimerLib::~TimerLib()
{
  this->m_stop = true;
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

/**
 * The first action is emitted immediatelly, then wait
 * specified time and emit next action
 */
void TimerLib::execute()
{  
  // Split the timeout to 100 ms stages, to improve thread handling
  int milliseconds = m_timeout;
  bool m_break = false;
  int steps = milliseconds / TIMERLIB_TIMEOUT_STEPS_MS;
  int rest = milliseconds % TIMERLIB_TIMEOUT_STEPS_MS;
  
  while(! m_stop)
  {     
    for(int i = 0; i < steps; i++)
    {
      this->sleep(TIMERLIB_TIMEOUT_STEPS_MS);
      
      if(m_stop)
      {
	m_break = true;
	break;
      }
    }
    
    if(! m_break)
    {
      this->sleep(rest);
    }
    
    m_call();
  }
}

void TimerLib::sleep(int milliseconds)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

