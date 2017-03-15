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
    
    suiteOfTests->addTest(new CppUnit::TestCaller<TimerLibTest>("Short timeout timer",
				&TimerLibTest::createTimerObject));
    
    /*suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Prepare objects",
				&ThermometerTest::createThermometerObjects));

    suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Check objects",
				&ThermometerTest::checkThermometerObjects));

    suiteOfTests->addTest(new CppUnit::TestCaller<ThermometerTest>("Register objects",
				&ThermometerTest::registerThermometers));*/

    return suiteOfTests;
  }

protected:  
  void createTimerObject();

private:
  const int TEST_SHORT_TIMEOUT = 50;
  
  bool called;
  TimerLib *timer;
  Supervision *supervision;
  
  void timeout();
};

#endif
