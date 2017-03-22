#include "timerlibtest.h"
#include "../lib/logger.h"
#include "../lib/supervision.h"

#include <functional>
#include <thread>

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

void TimerLibTest::middleTimeout_100_ms()
{
  this->testTimeout(TEST_MIDDLE_TIMEOUT);
}

void TimerLibTest::longTimeout_600_ms()
{
  this->testTimeout(TEST_LONG_TIMEOUT);
}

void TimerLibTest::secondsTimeout_1_s()
{
  this->testTimeout(TEST_SECONDS_TIMEOUT);
}

void TimerLibTest::repetitiveTimeout_100ms()
{
  this->testRepetitiveTimeout(TEST_MIDDLE_TIMEOUT);
}

/**
 * Will signal received timeout and store it.
 */
void TimerLibTest::timeout()
{
  dbg << "Timeout occured";
  end = std::chrono::steady_clock::now();
  called = true;
}

void TimerLibTest::testTimeout(const int timeout)
{
  // loop up to two times period
  int loops = TIMEOUT_LOOP(timeout);
  //int timeDiff = 0, spentTime = 0;
  std::chrono::steady_clock::duration spentTime;
  bool bigTimeDiff = false, lowTimeDiff = false;
  std::string reason = "";
  
  std::thread supervisionThread(&Supervision::init, supervision);  
  TimeoutCallback callback = std::bind(&TimerLibTest::timeout, this);
  timer = new TimerLib(callback, timeout);
  start = std::chrono::steady_clock::now();
  timer->start();
  
  while(!called && (loops > 0) )
  {
    // sleep for watchdog period, should be smaller than m_timeout
    std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_TEST_WATCHDOG_MS));
    loops--;
  }
  timer->stopExecution();

  spentTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  
  dbg << "Stop supervision threads";
  
  supervision->stop(reason);
  supervisionThread.join();
  
  dbg << "Spent time: " << spentTime.count();
  reason.append("Unit test finished");
  
  if(loops <= 0 || spentTime.count() > ((timeout + TIMER_PLUS_SPAN) * 1000000 )) 
  {
    errn << "Timer took more time than expected, more than time + span" ;
    bigTimeDiff = true; 
    
    reason.append(" loops: ");
    reason.append(std::to_string(loops));
    reason.append(" callback: ");
    reason.append(std::to_string(called));
    reason.append(" sleep for: ");
    reason.append(std::to_string(timeout));
    reason.append(" spent: ");
    reason.append(std::to_string(spentTime.count()));
    bigTimeDiff = true;
  }
  else if(spentTime.count() < ((timeout) * 1000000 ))
  {
    errn << "Time took less time than expected";
    lowTimeDiff = true;
  }
  
  CPPUNIT_ASSERT(!bigTimeDiff);
  CPPUNIT_ASSERT(!lowTimeDiff);
  CPPUNIT_ASSERT(loops > 0);
  CPPUNIT_ASSERT(called);
}

void TimerLibTest::testRepetitiveTimeout(const int timeout)
{
  dbg << "Start repetitive test " << timeout;
}

