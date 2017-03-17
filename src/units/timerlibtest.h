#ifndef UNITS_TIMERLIBTEST_H_
#define UNITS_TIMERLIBTEST_H_

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCase.h>

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
				&TimerLibTest::shortTimeout_100_ms));
    
    /*suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Prepare objects",
				&ThermometerTest::createThermometerObjects));

    suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Check objects",
				&ThermometerTest::checkThermometerObjects));

    suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Register objects",
				&ThermometerTest::registerThermometers));*/

    return suiteOfTests;
  }

protected:  
  void shortTimeout_50_ms();
  void shortTimeout_100_ms();

private:
  const int TIMER_TEST_WATCHDOG_MS = 5;
  const int TEST_SHORT_TIMEOUT = 50;
  const int TEST_MIDDLE_TIMEOUT = 100;
  const int TEST_LONG_TIMEOUT = 600;
  const int TEST_SECONDS_TIMEOUT = 1000;
  
  bool called;
  TimerLib *timer;
  Supervision *supervision;
  
  void timeout();
  void testTimeout(const int m_timeout);
};

#endif
