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
  this->loadConfiguration();
}

bool Supervision::loadConfiguration()
{
  Configuration conf(m_conf);
  
  conf.loadConfiguration();
}

void Supervision::setConfigurationFile(const std::string& conf)
{
  m_conf = conf;
}



