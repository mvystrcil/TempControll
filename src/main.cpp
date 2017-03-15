#include "lib/logger.h"

#include "lib/supervision.h"
#include "lib/timerlib.h"
#include "consts/exitcodes.h"
#include "consts/loglevels.h"

#include <string>
#include <thread>
#include <unistd.h>
#include <signal.h>

#ifndef _UNIT_TESTS

static std::string configurationFile = "";
static std::string debugFile = "temp.log";
static LogLevel debugLevel;
static Supervision supervision;

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


void handleSignals(int signal)
{
  std::string reason = "Received signal ";
  reason.append(std::to_string(signal));
  
  supervision.stop(reason);
}

bool registerSignals()
{
  struct sigaction handler;
  handler.sa_handler = handleSignals;
  sigemptyset(&(handler.sa_mask));
  handler.sa_flags = 0;
  
  sigaction(SIGINT, &handler, nullptr);
  
  return true;
}

int main(int argc, char* argv[])
{
  registerSignals();
  
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
  
  supervision.setConfigurationFile(configurationFile);
  std::thread supervisionThread(&Supervision::init, &supervision);
  
  supervisionThread.join();
  
  warn << "Exiting application";
  Logger::finishLogSession();
 
  return 0;	
}
#endif
