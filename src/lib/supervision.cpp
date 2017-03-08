#include "supervision.h"
#include "logger.h"

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
  dbg << "Init by thread ";
  
  initThermometers();
  
  dbg << "Supervision thread will poll ";
  
  while(! stop)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  
  warn << "Supervision thread stopped";
}

void Supervision::initThermometers()
{
  dbg << "Create all instances for thermometers";
  
  /*th1 = Thermometer("A");
  th2 = Thermometer("B");
  list.registerThermometer(th1);
  list.registerThermometer(th2);*/
  
  stats.startStatsColl();
}



