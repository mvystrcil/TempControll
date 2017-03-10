#include "thermometer.hpp"
#include "../lib/logger.h"

Thermometer::Thermometer(const string &name, const std::string &address)
{
    this->name = name;
    this->address = address;
    this->temperature = 0;
    this->updatePeriod = 0;
}

Thermometer::~Thermometer()
{
}

string Thermometer::getThermometerName() const
{
    return this->name;
}

int Thermometer::getTemperature() const
{
	return this->temperature;
}

bool Thermometer::updateTemperature(const int temperature)
{
    this->temperature = temperature;

    return true;
}

bool Thermometer::setMinMaxTemp(const double min, const double max)
{
  if(min >= max)
  {
    warn << "Thermometer: " << this->name;
    warn << "Max temp " << max << " min temp " << min << " not possible";
    return false;
  }
  
  this->minTemp = min;
  this->maxTemp = max;
}

bool Thermometer::operator ==(const Thermometer& other) const
{
    if(this->getThermometerName().compare(other.getThermometerName()) == 0)
    {
        return true;
    }

    return false;
}
