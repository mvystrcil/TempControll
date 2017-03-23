#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
 
#include "thermometertest.h"
#include "timerlibtest.h"
#include "databasetest.h"
#include "../lib/logger.h"
 
int main() {
  Logger::setReportingLevel(DEBUG);
  Logger::setLogToConsole(false);
  Logger::setLogToFile("units.log");
  
  CppUnit::TextUi::TestRunner runner;
  
  runner.addTest(ThermometerTest::suite());
  runner.addTest(TimerLibTest::suite());  
  runner.addTest(DatabaseTest::suite());
  
  dbg << "Running the unit tests.";
  runner.run();
  
  return 0;
}
