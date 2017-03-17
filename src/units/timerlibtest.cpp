#include "timerlibtest.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"

#include <functional>
#include <thread>
#include <chrono>

#define TIMEOUT_LOOP(m_timeout) (2 * (m_timeout / TIMER_TEST_WATCHDOG_MS))

void TimerLibTest::setUp()
{
  called = false;
  supervision = new Supervision();
}

void TimerLibTest::tearDown()
{
  supervision->stop("Unit testing");
  
  delete(supervision);
}

void TimerLibTest::shortTimeout_50_ms()
{
  this->testTimeout(TEST_SHORT_TIMEOUT);
}

void TimerLibTest::shortTimeout_100_ms()
{
  this->testTimeout(TEST_MIDDLE_TIMEOUT);
}

/**
 * Will signal received timeout and store it.
 */
void TimerLibTest::timeout()
{
  called = true;
}

void TimerLibTest::testTimeout(const int m_timeout)
{
  // loop up to two times period
  int loops = TIMEOUT_LOOP(m_timeout);
  int timeDiff = 0;
  bool bigTimeDiff = false;
  std::string reason = "";
  
  std::thread supervisionThread(&Supervision::init, supervision);  
  TimeoutCallback callback = std::bind(&TimerLibTest::timeout, this);
  timer = new TimerLib(callback, m_timeout);
  timer->start();
  
  while(!called && (loops > 0) )
  {
    // sleep for watchdog period, should be smaller than m_timeout
    std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_TEST_WATCHDOG_MS));
    loops--;
  }
  timeDiff = (TIMEOUT_LOOP(m_timeout) - loops) * TIMER_TEST_WATCHDOG_MS;
  dbg << "TimeDiff: " << timeDiff << " timeout: " << m_timeout;
  reason.append("Unit test finished");
  
  if(timeDiff > 2 * TIMER_TEST_WATCHDOG_MS)
  {
    reason.append(" loops: ");
    reason.append(std::to_string(loops));
    reason.append(" callback: ");
    reason.append(std::to_string(called));
    reason.append(" sleep for: ");
    reason.append(std::to_string(m_timeout));
    reason.append(" diff: ");
    reason.append(std::to_string(TIMER_TEST_WATCHDOG_MS * (TIMEOUT_LOOP(m_timeout) - loops)));
    bigTimeDiff = true;
  }
  supervision->stop(reason);
  supervisionThread.join();
  
  CPPUNIT_ASSERT(! bigTimeDiff);
  CPPUNIT_ASSERT(loops > 0);
  CPPUNIT_ASSERT(called);
}
