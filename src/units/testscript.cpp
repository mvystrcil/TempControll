#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <unistd.h>

#include "thermometertest.h"
#include "timerlibtest.h"
#include "databasetest.h"
#include "../lib/logger.h"

static bool consoleEnabled = false;
static bool timeAndTempTest = false;
static bool databaseTest = false;

bool parseInputArgs(int argc, char *argv[])
{
  char opt;
  std::string optArgument = "";
  
  dbg << "Parsing input arguments";
  
  while((opt = getopt(argc, argv, "actd")) != -1)
  {
    switch(opt)
    {
      case 'c':
	consoleEnabled = true;
	break;
	
      case 't':
	timeAndTempTest = true;
	break;
	
      case 'd':
	databaseTest = true;
	break;
	
      case 'a':
	timeAndTempTest = true;
	databaseTest = true;
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
  
  if(! parseInputArgs(argc, argv))
  {
    errn << "Cannot parse input arguments";
  }
  
  Logger::setLogToConsole(consoleEnabled);
  Logger::setLogToFile("units.log");
  
  CppUnit::TextUi::TestRunner runner;
  
  if(timeAndTempTest)
  {
    runner.addTest(ThermometerTest::suite());
    runner.addTest(TimerLibTest::suite());  
  }
  
  if(databaseTest)
  {
    runner.addTest(DatabaseTest::suite());
  }
  
  dbg << "Running the unit tests.";
  runner.run();
  
  return 0;
}
