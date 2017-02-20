#include "thermometerstatistics.h"

#include <iostream>
#include "thermometerslist.h"

using namespace std;

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

bool ThermometerStatistics::startStatsColl() const
{
    this->updateAllThermometers();
    return true;
}


/*
 * Private functions implementation
*/

void ThermometerStatistics::updateAllThermometers() const
{
    ThermometersList& list = ThermometersList::getInstance();
    vector<Thermometer> array = list.getRegisteredList();

    vector<Thermometer>::iterator it = array.begin();

    for(it; it != array.end(); it++)
    {
        Thermometer &thermometer = *it;
        cout << "Temp for " << thermometer.getThermometerName() << " " << thermometer.getTemperature() << endl;
    }
}
