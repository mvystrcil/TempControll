#include "supervision.h"
#include "logger.h"
#include "thermometer/thermometerstatistics.h"
#include "thermometer/thermometerslist.h"
#include "thermometer/thermometerstatistics.h"

#include <thread>
#include <iostream>

Supervision::Supervision()
{
  dbg << "Prepare supervision object";
  stop = false;
}

Supervision::~Supervision()
{

}

void Supervision::init()
{
  int i = 0;
  std::cout << "Init" << std::endl;
  
  while(!stop && i < 50)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
    dbg << "Wait for action";
  }
}

void Supervision::initThermometers()
{
  dbg << "Create all instances for thermometers";
  
  ThermometerStatistics stats;
  Thermometer th1("AA");
  Thermometer th2("BB");
  
  dbg << "Starting program to collect all incoming data";
  ThermometersList& list = ThermometersList::getInstance();
  
  list.registerThermometer(th1);
  list.registerThermometer(th2);
  
  stats.startStatsColl();
}



