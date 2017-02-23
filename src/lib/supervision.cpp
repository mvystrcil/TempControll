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
  //dbg << "Initializing" << lf;
  std::cout << "Init" << std::endl;
  // Do what has to be done....
  
  while(!stop && i < 50)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
    dbg << "Wait for action";
  }
}

