#include "thermometerstatistics.h"
#include "thermometerslist.h"
#include "../lib/logger.h"

using namespace std::placeholders;

ThermometerStatistics::ThermometerStatistics(int updateTimeout) : updateTimeout(updateTimeout)
{
}

int ThermometerStatistics::getUpdateTimeout() const
{
    return this->updateTimeout;
}

bool ThermometerStatistics::setUpdateTimeout(const int timeout)
{
  if(timeout <= 0)
  {
    warn << "Trying to set timeout <= 0: " << timeout << " not possible";
    warn << "Will use previous value: " << this->updateTimeout;
    return false;
  } 
  
  this->updateTimeout = timeout;
  return true;
}

bool ThermometerStatistics::startStatsColl()
{
  dbg << "Register callback";
  TimeoutCallback callback = std::bind(&ThermometerStatistics::updateAllThermometers, this);
  dbg << "fin";
  
  timer = new TimerLib(callback, this->getUpdateTimeout());
  timer->start();
  
  return true;
}

bool ThermometerStatistics::stopStatsColl() const
{
  timer->stopExecution();
  return true;
}



/*
 * Private functions implementation
*/

void ThermometerStatistics::updateAllThermometers(void)
{  
  ThermometersList& list = ThermometersList::getInstance();
  vector<Thermometer *> array = list.getRegisteredList();
  vector<Thermometer *>::iterator it = array.begin();
  
  for(it; it != array.end(); it++)
  {
    Thermometer *thermometer = *it;
    dbg << "Temp " << thermometer->getThermometerName() << "\t" << thermometer->getTemperature();
  }
}
