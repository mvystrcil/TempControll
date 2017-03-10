#include "supervision.h"
#include "logger.h"

#include <thread>
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
}

void Supervision::setConfigurationFile(const std::string& conf)
{
  m_conf = conf;
}



