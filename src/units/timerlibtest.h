#ifndef UNITS_TIMERLIBTEST_H_
#define UNITS_TIMERLIBTEST_H_

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>
#include <chrono>

#include "../lib/supervision.h"
#include "../lib/timerlib.h"

class TimerLibTest : public CppUnit::TestFixture
{

public:
  void setUp();
  void tearDown();

  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TimerLibTest cases");

    // Register all test functions
    
    suiteOfTests->addTest(new CppUnit::TestCaller<TimerLibTest>("50ms timeout timer",
				&TimerLibTest::shortTimeout_50_ms));
    
    suiteOfTests->addTest(new CppUnit::TestCaller<TimerLibTest>("100ms timeout timer",
				&TimerLibTest::middleTimeout_100_ms));
    
    suiteOfTests->addTest(new CppUnit::TestCaller<TimerLibTest>("600ms timeout timer",
				&TimerLibTest::longTimeout_600_ms));
    
    suiteOfTests->addTest(new CppUnit::TestCaller<TimerLibTest>("1000ms timeout timer",
				&TimerLibTest::secondsTimeout_1_s));
    
    suiteOfTests->addTest(new CppUnit::TestCaller<TimerLibTest>("100ms repetitive timer",
				&TimerLibTest::repetitiveTimeout_100ms));

    return suiteOfTests;
  }

protected:  
  void shortTimeout_50_ms();
  void middleTimeout_100_ms();
  void longTimeout_600_ms();
  void secondsTimeout_1_s();
  void repetitiveTimeout_100ms();

private:
  const int TIMER_TEST_WATCHDOG_MS = 5;
  const int TIMER_PLUS_SPAN = 20;
  const int TIMER_MINUS_SPAN = 10;
  const int TEST_SHORT_TIMEOUT = 50;
  const int TEST_MIDDLE_TIMEOUT = 100;
  const int TEST_LONG_TIMEOUT = 600;
  const int TEST_SECONDS_TIMEOUT = 1000;
  
  const int TEST_REPETITIVE_REPEAT_10 = 10;
  
  bool called;
  TimerLib *timer;
  Supervision *supervision;
  std::thread supervisionThread;
  
  std::chrono::steady_clock::time_point start, end;	
  
  void timeout();
  void testTimeout(const int timeout);
  void testRepetitiveTimeout(const int timeout, const int repetitions);
  
  inline void startTimerAndLogTimestamp(const int timeout);
  void processResults(const std::chrono::steady_clock::duration& spent, const int loops, const int timeout);
};

#endif
