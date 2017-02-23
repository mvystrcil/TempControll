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

bool ThermometerStatistics::setUpdateTimeout(const int updateTimeout)
{
    this->updateTimeout = updateTimeout;
    return true;
}

bool ThermometerStatistics::startStatsColl()
{
  TimeoutCallback callback = std::bind(
    &ThermometerStatistics::updateAllThermometers, this);
  
  timer.registerHandler(callback, 200);
  
  return true;
}

bool ThermometerStatistics::stopStatsColl() const
{
  return true;
}



/*
 * Private functions implementation
*/

void ThermometerStatistics::updateAllThermometers(void)
{
    ThermometersList& list = ThermometersList::getInstance();
    vector<Thermometer> array = list.getRegisteredList();

    vector<Thermometer>::iterator it = array.begin();

    for(it; it != array.end(); it++)
    {
        Thermometer &thermometer = *it;
        dbg << "Temp " << thermometer.getThermometerName() << thermometer.getTemperature();
    }
}
