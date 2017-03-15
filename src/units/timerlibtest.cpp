#include "timerlibtest.h"
#include "../lib/logger.h"

#include <functional>
#include <thread>

void TimerLibTest::setUp()
{
  called = false;
  supervision = new Supervision();
}

void TimerLibTest::tearDown()
{
  
}

void TimerLibTest::createTimerObject()
{
  int loops = 3;
  TimeoutCallback callback = std::bind(&TimerLibTest::timeout, this);
  timer = new TimerLib(callback, TEST_SHORT_TIMEOUT);
  timer->start();
  
  while(!callback && ! loops )
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(TEST_SHORT_TIMEOUT));
    loops--;
  }
  
  CPPUNIT_ASSERT(loops > 0);
  CPPUNIT_ASSERT(called);
}

/**
 * Will signal received timeout and store it.
 */
void TimerLibTest::timeout()
{
  dbg << "Timeout";
  called = true;
}
