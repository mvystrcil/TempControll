#include "timerlib.h"
#include "../lib/logger.h"

#include <chrono>

TimerLib::TimerLib()
{

}

int TimerLib::registerHandler(TimeoutCallback callback, int timeout)
{
  Event event(callback, timeout);
  int last_item = PROBLEM_WHILE_THREAD_CREATION;
  
  threads.push_back(event);
  last_item = threads.size() - 1;
  
  std::thread m_execution(&Event::timeout, &event);
  m_execution.detach();
  
  dbg << "Register callback to fire every " << timeout << " in slot " << last_item;
  
  return last_item;
}

bool TimerLib::stopExecution()
{
  return true;
}

TimerLib::Event::Event(TimeoutCallback callback, int timeout): m_callback(callback), m_timeout(timeout)
{
  
}

void TimerLib::Event::timeout()
{
  while(! m_stop)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timeout));
    m_callback();
  }
}
