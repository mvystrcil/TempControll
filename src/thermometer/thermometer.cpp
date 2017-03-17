#include "thermometer.hpp"
#include "../lib/logger.h"
#include "../consts/timeouts.h"

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

int Thermometer::getTemperature()
{
  std::chrono::steady_clock::time_point act = std::chrono::steady_clock::now();
  int delay = (std::chrono::duration_cast<std::chrono::seconds>(act - lastUpdate)).count();
    
  // This is here to protect thermometers from reading very often
  // If last value is younger than THERMOMETER_READ_TEMPERATURE_MIN_PAUSE,
  // use the cached one
  if(delay > THERMOMETER_READ_TEMPERATURE_MIN_PAUSE)
  {
    this->readTemperature();
  }
  
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

bool Thermometer::setAddress(const string& address)
{
  this->address = address;
}

bool Thermometer::operator ==(const Thermometer& other) const
{
    if(this->getThermometerName().compare(other.getThermometerName()) == 0)
    {
        return true;
    }

    return false;
}

const double Thermometer::readTemperature()
{
  lastUpdate = std::chrono::steady_clock::now();
  return 24.3;
}
