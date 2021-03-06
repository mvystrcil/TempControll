#include "thermometerstatistics.h"
#include "thermometerslist.h"
#include "../lib/logger.h"
#include "lib/database/database_factory.h"
#include "lib/database/createtable.h"

using namespace std::placeholders;

ThermometerStatistics::ThermometerStatistics(int updateTimeout) : updateTimeout(updateTimeout)
{
}

ThermometerStatistics::~ThermometerStatistics()
{
  if(timer)
  {
    timer->stopExecution();
    delete(timer);
    timer = nullptr;
  }
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
  
  this->updateTimeout = timeout * 1000;
  return true;
}

bool ThermometerStatistics::startStatsColl()
{
  dbg << "Start collecting thermometer statistics " << this->getUpdateTimeout();
  TimeoutCallback callback = std::bind(&ThermometerStatistics::updateAllThermometers, this);
  
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
  vector<Thermometer *>::iterator it;
  
  for(it = array.begin(); it != array.end(); it++)
  {
    IThermometer *thermometer = *it;
    this->storeThermometerData(thermometer);
  }
}

bool ThermometerStatistics::storeThermometerData(const IThermometer* thermometer)
{
  dbg << "Store thermometer: " << thermometer->getThermometerName() << " temp: " << thermometer->getTemperature();
  
  return true;
}

bool ThermometerStatistics::preparePersistentStorage()
{
  CreateTable thermometerStats("ThermometerStats");
  SQLColumn id("ID", SQLTypes::INT, true, true, true);
  SQLColumn name("Name", SQLTypes::STRING);
  SQLColumn address("Address", SQLTypes::STRING);
  SQLColumn temperature("Temperature", SQLTypes::DOUBLE);
  
  thermometerStats.appendColumn(id);
  thermometerStats.appendColumn(name);
  thermometerStats.appendColumn(address);
  thermometerStats.appendColumn(temperature);
  
  
  
  database = DatabaseFactory::getInstance().getDatabase(DatabaseFactory::DatabaseTypes::SQLITE);
  
  return true;
}


