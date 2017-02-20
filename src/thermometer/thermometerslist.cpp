#include "thermometerslist.h"

#include <iostream>

ThermometersList* ThermometersList::instance = NULL;

ThermometersList::ThermometersList()
{

}

ThermometersList::~ThermometersList()
{
    delete(instance);
    instance = NULL;
}

ThermometersList* ThermometersList::getInstance()
{
    if(ThermometersList::instance == NULL)
    {
        instance = new ThermometersList();
    }

    return instance;
}

bool ThermometersList::registerThermometer(const Thermometer &thermometer)
{
    vector<Thermometer>::iterator iterator = this->meters.begin();

    for(iterator; iterator != this->meters.end(); iterator++)
    {
        Thermometer &th = *iterator;
        if(th == thermometer)
        {
            return false;
        }
    }

    cout << "Append thermometer " << thermometer.getThermometerName() << endl;
    this->meters.push_back(thermometer);

    return true;
}

bool ThermometersList::unregisterThermometer(const Thermometer &thermometer)
{
    vector<Thermometer>::iterator it = this->meters.begin();

    for(it; it != this->meters.end(); it++)
    {
        Thermometer &th = *it;
        if(th == thermometer)
        {
            this->meters.erase(it);
            return true;
        }
    }

    return false;
}

vector<Thermometer> ThermometersList::getRegisteredList() const
{
    return this->meters;
}
