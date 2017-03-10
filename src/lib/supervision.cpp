#include "supervision.h"
#include "logger.h"

#include <thread>
#include <chrono>
#include <iostream>

Supervision::Supervision()
{
  stop = false;
}

Supervision::~Supervision()
{

}

void Supervision::init()
{
  if(! this->loadConfiguration())
  {
    return;
  }
}

bool Supervision::loadConfiguration()
{
  Configuration conf(m_conf);
  
  if(! conf.loadConfiguration(statistics))
  {
    err << "Configuration load failed";
    return false;
  }
  
  return this->supervise();
}

void Supervision::setConfigurationFile(const std::string& conf)
{
  m_conf = conf;
}

bool Supervision::supervise()
{
  info << "Configuration loaded from file: " << m_conf << " go to supervise state";
  
  while(!stop)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(SUPERVISE_PERIOD_CHECK_MS));
  }
  
  if(stop)
  {
    info << "Intentional stop, bye";
    return true; 
  }
  else
  {
    err << "Some other type of stop, most probably failed";
    return false;
  }
}




