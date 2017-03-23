#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <unistd.h>

#include "thermometertest.h"
#include "timerlibtest.h"
#include "databasetest.h"
#include "../lib/logger.h"

static bool consoleEnabled = false;

bool parseInputArgs(int argc, char *argv[])
{
  char opt;
  std::string optArgument = "";
  
  dbg << "Parsing input arguments";
  
  while((opt = getopt(argc, argv, "c:")) != -1)
  {
    switch(opt)
    {
      case 'c':
	consoleEnabled = true;
	break;
      
      default:
	warn << "Unknown program argument " << opt;return false;
	break;
    }
  }
  
  return true;
}

int main(int argc, char *argv[]) { 
  Logger::setReportingLevel(DEBUG);
  Logger::setLogToConsole(consoleEnabled);
  Logger::setLogToFile("units.log");
  
  CppUnit::TextUi::TestRunner runner;
  
  runner.addTest(ThermometerTest::suite());
  runner.addTest(TimerLibTest::suite());  
  runner.addTest(DatabaseTest::suite());
  
  dbg << "Running the unit tests.";
  runner.run();
  
  return 0;
}
