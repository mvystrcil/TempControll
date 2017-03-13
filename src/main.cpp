#include "lib/logger.h"

#include "lib/supervision.h"
#include "lib/timerlib.h"
#include "consts/exitcodes.h"
#include "consts/loglevels.h"

#include <string>
#include <thread>
#include <unistd.h>

#ifndef _UNIT_TESTS

static std::string configurationFile = "";
static std::string debugFile = "temp.log";
static LogLevel debugLevel;

bool checkMandatoryParameters()
{
  if(configurationFile.compare("") == 0)
  {
    errn << "Configuration file cannot be empty string";
    return false;
  }
  
  if(debugFile.compare("") == 0)
  {
    errn << "Debug file is set, but cannot be empty string";
    return false; 
  }
  
  return true;
}

bool parseInputArgs(int argc, char *argv[])
{
  char opt;
  std::string optArgument = "";
  
  dbg << "Parsing input arguments";
  
  while((opt = getopt(argc, argv, "c:d:f:")) != -1)
  {
    switch(opt)
    {
      case 'c':
	configurationFile = optarg;
	break;
	
      case 'd':
	optArgument = optarg;
	
	//
	// TODO: make some mapping of log levels
	// 
	if(optArgument.compare("debug") == 0)
	{
	  debugLevel = DEBUG;
	}
	else
	{
	  debugLevel = INFO;
	}	
	break;
	
      case 'f':
	debugFile = optarg;	
	break;
	
      default:
	warn << "Unknown program argument " << opt;
	return false;
	break;
    }
  }
  
  return checkMandatoryParameters();
}

int main(int argc, char* argv[])
{
  // This has to be the first command
  Logger::setReportingLevel(DEBUG);
  
  dbg << "Parse";
  
  if(! parseInputArgs(argc, argv))
  {
    errn << "Cannot parse input arguments, will exit";
    return BREAK_INPUT_ARGUMENTS;
  }
  
  Logger::setReportingLevel(debugLevel);
  Logger::setLogToFile(debugFile);
  
  Supervision supervision;  
  supervision.setConfigurationFile(configurationFile);
  std::thread supervisionThread(&Supervision::init, &supervision);
  
  supervisionThread.join();
  
  warn << "Exiting application";
  Logger::finishLogSession();
 
  return 0;	
}
#endif
