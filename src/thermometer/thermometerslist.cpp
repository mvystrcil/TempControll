#include "thermometerslist.h"
#include "../lib/logger.h"

std::vector<Thermometer *> ThermometersList::meters;

ThermometersList::ThermometersList()
{
  
}

ThermometersList::~ThermometersList()
{
  dbg << "Destructor called";
  this->unregisterAllThermometers();
}

ThermometersList& ThermometersList::getInstance()
{
  static ThermometersList instance;
  return instance;
}

void ThermometersList::resetInstance()
{
  // Do nothing right now
}

bool ThermometersList::registerThermometer(Thermometer *thermometer)
{
  vector<Thermometer *>::iterator iterator;
  
  for(iterator = this->meters.begin(); iterator != this->meters.end(); iterator++)
  {
    Thermometer *th = *iterator;
    if(th == thermometer)
    {
      return false; 
    }
  }

  dbg << "Append thermometer " << thermometer->getThermometerName();
  this->meters.push_back(thermometer);
  
  return true;
}

bool ThermometersList::unregisterThermometer(const Thermometer* thermometer)
{
  vector<Thermometer *>::iterator it;
  
  for(it = this->meters.begin(); it != this->meters.end(); it++)
  {
    Thermometer *th = *it;
    if(th == thermometer)
    {
      info << "Erase thermometer " << th->getThermometerName();
      delete(th);
      this->meters.erase(it);
      return true;
    }
  }
  
  return false;
}

bool ThermometersList::unregisterAllThermometers()
{
  vector<Thermometer *> list = this->getRegisteredList();
  vector<Thermometer *>::iterator iterator = list.begin();
  Thermometer *thermometer;
  
  while(iterator != list.end())
  {
    thermometer = *iterator;
    this->unregisterThermometer(thermometer);
    iterator++;
  }
  
  return true;
}

vector<Thermometer *> ThermometersList::getRegisteredList() const
{
  return this->meters;
}
