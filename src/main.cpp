#include "lib/logger.h"

#include "lib/supervision.h"
#include "lib/timerlib.h"

#include <string>
#include <thread>

#ifndef _UNIT_TESTS

int main(int argc, char* argv[])
{
  Logger::setReportingLevel(DEBUG);
  Logger::setLogToFile("temp.log");
  
  Supervision supervision;  
  supervision.setConfigurationFile(".");
  std::thread supervisionThread(&Supervision::init, &supervision);
  
  supervisionThread.join();
  
  warn << "Exiting application";
  Logger::finishLogSession();
 
  return 0;	
}
#endif
