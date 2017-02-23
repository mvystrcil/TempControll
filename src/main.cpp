#include "lib/logger.h"
#include "thermometer/thermometerstatistics.h"
#include "thermometer/thermometerslist.h"
#include "thermometer/thermometerstatistics.h"
#include "lib/timerlib.h"

#include <string>

#ifndef _UNIT_TESTS

int main(int argc, char* argv[])
{
  Logger::setReportingLevel(DEBUG);
  Logger::setLogToFile("temp.log");
  
  ThermometerStatistics stats;
  Thermometer th1("AA");
  Thermometer th2("BB");
  
  dbg << "Starting program to collect all incoming data";
  ThermometersList& list = ThermometersList::getInstance();
  
  list.registerThermometer(th1);
  list.registerThermometer(th2);
  
  stats.startStatsColl();
  return 0;	
}
#endif
